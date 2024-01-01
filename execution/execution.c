/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:43:44 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/29 20:20:49 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

extern t_global	g_global;

void	ft_child_process(t_node *node, char ***envp, int *fd)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (node->pipe)
		close(fd[0]);
	redirection(node);
	if (node->amb)
		exit(print_amb_msg(node));
	else if (node->file_not_found)
		exit(print_file_not_found_msg(node));
	else if (node->pd)
		exit(print_permission_msg(node));
	else if (node->isd)
		exit(print_isd_msg(node));
	else if (node->cmd_not_found)
		exit(print_cmd_not_found_msg(node));
	else if (ft_is_builtin(node->cmd))
		exit(exec_builtin(node, envp));
	else
		exit(execve(node->cmd, node->args, *envp));
}

void	wait_for_child(int status)
{
	while (waitpid(-1, NULL, 0) > 0)
		;
	if (WIFEXITED(status))
		g_global.status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_global.status = WTERMSIG(status) + 128;
	signal(SIGINT, crt_c);
}

void	exec_commands(t_node *node, char ***envp, int is_pipeline)
{
	int			pid;
	int			fd[2];
	int			status;
	t_fd_recall	recall;

	if (node->pipe)
		ft_pipe_setup(node, fd);
	if (ft_is_builtin(node->cmd) && !node->pipe && !is_pipeline)
		recall = setup_and_exec_builtin(node, envp);
	else
	{
		pid = fork();
		if (pid == 0)
			ft_child_process(node, envp, fd);
		signal(SIGINT, SIG_IGN);
	}
	if (ft_is_builtin(node->cmd))
		ft_close_builtin(node, recall);
	else
		ft_close(node);
	if (node->next)
		exec_commands(node->next, envp, is_pipeline);
	if (!(ft_is_builtin(node->cmd) && !is_pipeline)
		&& waitpid(pid, &status, 0) > 0)
		wait_for_child(status);
}

void	execution(t_node *node, char ***envp)
{
	int		is_pipeline;

	if (node->pipe)
		is_pipeline = 1;
	else
		is_pipeline = 0;
	exec_commands(node, envp, is_pipeline);
}
