/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:15:58 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 20:21:35 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

int	is_dir(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

void	free_t_node(t_node *cmd)
{
	t_node	*tmp;

	while (cmd)
	{
		free(cmd->cmd);
		free(cmd->amb_msg);
		free(cmd->file_msg);
		cmd->cmd = NULL;
		my_free(cmd->args);
		cmd->args = NULL;
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_tokens_list(t_list *tokens_list)
{
	t_list	*tmp;

	while (tokens_list)
	{
		free(((t_token *)(tokens_list->content))->token);
		if (((t_token *)(tokens_list->content))->amb_msg)
			free(((t_token *)(tokens_list->content))->amb_msg);
		if (((t_token *)(tokens_list->content))->file_msg)
			free(((t_token *)(tokens_list->content))->file_msg);
		free(((t_token *)(tokens_list->content))->token_meta);
		if (((t_token *)(tokens_list->content))->expand)
			free(((t_token *)(tokens_list->content))->expand);
		tmp = tokens_list;
		tokens_list = tokens_list->next;
		free(((t_token *)(tmp->content)));
		free(tmp);
	}
}

void	free_fdlist(t_list *fd)
{
	t_list	*tmp;

	while (fd)
	{
		tmp = fd;
		free(((t_fd *)(tmp->content))->file_msg);
		free(((t_fd *)(tmp->content))->amb_msg);
		free(((t_fd *)(tmp->content)));
		fd = fd->next;
		free(tmp);
	}
}

void	ultimate_free(t_data *data)
{
	free(data->promt);
	data->promt = NULL;
	free(data->promt_meta);
	data->promt_meta = NULL;
	free(data->split_info);
	data->split_info = NULL;
	free_t_node(data->cmd);
	data->cmd = NULL;
	free_tokens_list(data->tokens_list);
	data->tokens_list = NULL;
	free_fdlist(data->fd);
	data->fd = NULL;
}
