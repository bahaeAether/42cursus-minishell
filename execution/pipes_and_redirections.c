/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:01:28 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/29 09:17:51 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

void	modify_fd(t_node *node, t_fd_recall *recall)
{
	if (node->input_redir || node->here_doc)
		recall->new_stdin = dup(0);
	if (node->output_redir || node->append_redir)
		recall->new_stdout = dup(1);
}

t_fd_recall	redirection_builtin(t_node *node)
{
	t_fd_recall	recall;

	recall.new_stdin = 0;
	recall.new_stdout = 1;
	modify_fd(node, &recall);
	redirection(node);
	return (recall);
}

void	redirection(t_node *node)
{
	if (node->input_redir)
	{
		dup2(node->input_redir, 0);
		close(node->input_redir);
	}
	if (node->output_redir)
	{
		dup2(node->output_redir, 1);
		close(node->output_redir);
	}
	if (node->append_redir)
	{
		dup2(node->append_redir, 1);
		close(node->append_redir);
	}
	if (node->here_doc)
	{
		dup2(node->here_doc, 0);
		close(node->here_doc);
	}
}

void	ft_pipe_setup(t_node *node, int *fd)
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("bash: echo: write error: Broken pipe\n", 2);
		exit(1);
	}
	if (node->output_redir)
		close(fd[1]);
	else
		node->output_redir = fd[1];
	if (node->next->input_redir)
		close(fd[0]);
	else
		node->next->input_redir = fd[0];
}
