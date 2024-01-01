/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:59:51 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 03:43:40 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

void	for_normstuff(t_list *tmp, t_fd *tmpo)
{
	tmpo->file_msg = ft_strdup(((t_token *)(tmp->next->content))->token);
	tmpo->isd++;
	tmpo->err++;
}

void	fill_err_in_cmd(t_node *cmd, t_list *tmpo)
{
	if (((t_fd *)(tmpo->content))->amb != 0 && cmd->amb_msg == NULL)
	{
		cmd->amb = 1;
		cmd->amb_msg = ft_strdup(((t_fd *)(tmpo->content))->amb_msg);
	}
	else if (((t_fd *)(tmpo->content))->fnf != 0 && cmd->file_msg == NULL)
	{
		cmd->file_not_found = 1;
		cmd->file_msg = ft_strdup(((t_fd *)(tmpo->content))->file_msg);
	}
	else if (((t_fd *)(tmpo->content))->isd != 0 && cmd->file_msg == NULL)
	{
		cmd->isd = 1;
		cmd->file_msg = ft_strdup(((t_fd *)(tmpo->content))->file_msg);
	}
	else if (((t_fd *)(tmpo->content))->pd != 0 && cmd->file_msg == NULL)
	{
		cmd->pd = 1;
		cmd->file_msg = ft_strdup(((t_fd *)(tmpo->content))->file_msg);
	}
}

void	add_cmd_node(t_data *lst, t_node *data)
{
	t_node	*tmp;

	tmp = lst->cmd;
	if (tmp)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = data;
	}
	else
		lst->cmd = data;
}

void	free_token_node(t_list *token)
{
	if (token)
	{
		free(((t_token *)(token->content))->token);
		free(((t_token *)(token->content))->token_meta);
		free(((t_token *)(token->content))->expand);
		free(token->content);
		free(token);
	}
}

void	remove_re(t_list *tokens)
{
	t_list	*tmp;
	t_list	*tmpo;

	tmp = tokens;
	while (tmp)
	{
		if (((t_token *)(tmp->content))->e_token_id != WORD && \
			((t_token *)(tmp->content))->e_token_id != PIPE)
		{
			if (((t_token *)(tmp->content))->token_num != 1)
			{
				tmpo = tmp;
				(tmp->previous->next) = (tmp->next->next);
				if ((tmp->next->next))
					(tmp->next->next->previous) = (tmp->previous);
				tmp = tmp->previous;
				free_token_node(tmpo->next);
				free_token_node(tmpo);
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
}
