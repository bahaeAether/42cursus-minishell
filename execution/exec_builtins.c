/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:05:22 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/29 12:29:29 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

extern t_global	g_global;

int	ft_is_builtin(char *cmd)
{
	if (cmd != NULL)
	{
		if (!ft_strcmp(cmd, "echo"))
			return (1);
		if (!ft_strcmp(cmd, "cd"))
			return (2);
		if (!ft_strcmp(cmd, "pwd"))
			return (3);
		if (!ft_strcmp(cmd, "export"))
			return (4);
		if (!ft_strcmp(cmd, "unset"))
			return (5);
		if (!ft_strcmp(cmd, "env"))
			return (6);
		if (!ft_strcmp(cmd, "exit"))
			return (7);
	}
	return (0);
}

int	exec_builtin(t_node *node, char ***envp)
{
	if (ft_is_builtin(node->cmd) == 1)
		return (ft_echo(node->args));
	else if (ft_is_builtin(node->cmd) == 2)
		return (ft_cd(node->args, envp));
	else if (ft_is_builtin(node->cmd) == 3)
		return (ft_pwd(*envp));
	else if (ft_is_builtin(node->cmd) == 4)
		return (ft_export(node->args, envp));
	else if (ft_is_builtin(node->cmd) == 5)
		return (ft_unset(node->args, envp));
	else if (ft_is_builtin(node->cmd) == 6)
		return (ft_env(*envp));
	else if (ft_is_builtin(node->cmd) == 7)
		return (ft_exit(node->args));
	return (0);
}

t_fd_recall	setup_and_exec_builtin(t_node *node, char ***envp)
{
	t_fd_recall	recall;

	recall = redirection_builtin(node);
	g_global.status = 1;
	if (node->amb)
		g_global.status = print_amb_msg(node);
	else if (node->pd)
		g_global.status = print_permission_msg(node);
	else if (node->file_not_found)
		g_global.status = print_file_not_found_msg(node);
	else if (node->isd)
		g_global.status = print_isd_msg(node);
	else
		g_global.status = exec_builtin(node, envp);
	return (recall);
}

void	ft_close_builtin(t_node *node, t_fd_recall recall)
{
	ft_close(node);
	dup2(recall.new_stdin, 0);
	dup2(recall.new_stdout, 1);
}

void	ft_close(t_node *node)
{
	if (node->input_redir)
		close(node->input_redir);
	if (node->output_redir)
		close(node->output_redir);
	if (node->append_redir)
		close(node->append_redir);
	if (node->here_doc)
		close(node->here_doc);
}
