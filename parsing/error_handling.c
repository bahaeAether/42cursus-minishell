/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:26:01 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:25:10 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

void	error_handling_pipe(t_list *tmp, int i, int *e)
{
	if (*e == 0 && ((t_token *)(tmp->content))->e_token_id == PIPE && \
		((t_token *)(tmp->content))->token_num == 1)
	{
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		g_global.status = 258;
		(*e)++;
	}
	else if (*e == 0 && ((t_token *)(tmp->content))->e_token_id == PIPE && \
		((t_token *)(tmp->content))->token_num == i)
	{
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		g_global.status = 258;
		(*e)++;
	}
	else if (*e == 0 && ((t_token *)(tmp->content))->e_token_id == PIPE && \
		tmp->next && (((t_token *)(tmp->next->content))->e_token_id == PIPE))
	{
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		g_global.status = 258;
		(*e)++;
	}
}

void	error_handling_redrection(t_list *tmp, int i, int *e)
{
	if (*e == 0 && (((t_token *)(tmp->content))->e_token_id == WRITE || \
	((t_token *)(tmp->content))->e_token_id == READ || \
	(((t_token *)(tmp->content))->e_token_id == HEREDOC || \
	((t_token *)(tmp->content))->e_token_id == APPEND)) && \
	((t_token *)(tmp->content))->token_num == i)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		g_global.status = 258;
		(*e)++;
	}
	else if (*e == 0 && (((t_token *)(tmp->content))->e_token_id == READ \
			|| (((t_token *)(tmp->content))->e_token_id == HEREDOC)) && \
		((t_token *)(tmp->next->content))->e_token_id != WORD)
	{
		ft_putstr_fd_next("syntax error near unexpected token", 2, tmp);
		(*e)++;
	}
	else if (*e == 0 && (((t_token *)(tmp->content))->e_token_id == WRITE \
			|| (((t_token *)(tmp->content))->e_token_id == APPEND)) && \
		((t_token *)(tmp->next->content))->e_token_id != WORD)
	{
		ft_putstr_fd_next("syntax error near unexpected token ", 2, tmp);
		(*e)++;
	}
}

static	void	normimmm(t_list *tmp)
{
	update_meta_all(tmp, 0);
	remove_quotes(tmp, 0, 0);
}

static	void	utils(t_data *data, t_list *tmp, int i, int *e)
{
	check_quotes(data, e);
	e_token_id_filler(tmp);
	while (tmp)
	{
		error_handling_pipe(tmp, i, e);
		if (e == 0 && ((t_token *)(tmp->content))->e_token_id == PIPE)
			g_global.status = 0;
		error_handling_redrection(tmp, i, e);
		should_expand(tmp, -1, 0);
		if (((t_token *)(tmp->previous)) == NULL)
		{
			((t_token *)(tmp->content))->token = \
			parameter_expansion(tmp, 0, 0, 0);
			normimmm(tmp);
		}
		else if (((t_token *)(tmp->previous)) && \
		((t_token *)(tmp->previous->content))->e_token_id != HEREDOC)
		{
			((t_token *)(tmp->content))->token = \
			parameter_expansion(tmp, 0, 0, 0);
			normimmm(tmp);
		}
		tmp = tmp->next;
	}
}

void	error_handling(t_list *tokens_list, t_data *data)
{
	t_list	*tmp;
	t_list	*tmpo;
	int		e;

	e = 0;
	if (tokens_list)
	{
		tmp = tokens_list;
		utils(data, tmp, ft_lstsize(tmp), &e);
		if (e == 0)
			redirections(data, tmp, &e, NULL);
		tmp = tokens_list;
		tmpo = data->fd;
		while (tmp)
		{
			if (e == 0 && ((t_token *)(tmp->content))->e_token_id == PIPE)
			{
				g_global.heredoc_c = 0;
				tmpo = tmpo->next;
			}
			heredoc(data, tmp, tmpo, &e);
			tmp = tmp->next;
		}
		data->f = e;
	}
}
