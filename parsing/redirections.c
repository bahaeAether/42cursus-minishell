/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:21:43 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 11:27:28 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

static	void	for_aide(t_list *tmp, t_fd *tmpo, int i, int j)
{
	if ((i == 0 || j == 12) && tmpo->err == 0)
	{
		tmpo->file_msg = ft_strdup(((t_token *)(tmp->next->content))->token);
		if (errno == 13 && j != 12)
			tmpo->pd++;
		else if (j == 12)
			tmpo->fnf++;
		tmpo->err++;
	}
	if (i == 1 && tmpo->err == 0)
	{
		if (tmpo->fdin != 0)
			close(tmpo->fdin);
		tmpo->fdin = ((t_token *)(tmp->content))->fdout;
		tmpo->r_t_n = ((t_token *)(tmp->content))->token_num;
	}
	if (i == 2 && tmpo->err == 0)
	{
		tmpo->file_msg = \
			ft_strdup(((t_token *)(tmp->next->content))->token);
		tmpo->pd++;
		tmpo->err++;
	}
}

static	void	help(t_list *tmp, int *e, t_fd *tmpo)
{
	DIR	*directory;

	directory = opendir(((t_token *)(tmp->next->content))->token);
	if (directory != NULL)
	{
		closedir(directory);
		if (tmpo->err == 0)
		{
			tmpo->file_msg = \
			ft_strdup(((t_token *)(tmp->next->content))->token);
			tmpo->isd++;
			tmpo->err++;
		}
	}
	else if (tmpo->err == 0)
	{
		((t_token *)(tmp->content))->fdout = \
		open(((t_token *)(tmp->next->content))->token, O_RDONLY);
		if ((tmpo->err == 0 && (*e) == 0 && \
			((t_token *)(tmp->content))->fdout == -1))
			for_aide(tmp, tmpo, 0, 12);
		for_aide(tmp, tmpo, 1, 0);
	}
}

static	int	utils(t_list *tmp, int i, t_fd *tmpo)
{
	DIR	*directory;

	directory = opendir(((t_token *)(tmp->next->content))->token);
	if (directory != NULL)
	{
		for_normstuff(tmp, tmpo);
		closedir(directory);
	}
	else if (tmpo->err == 0 && \
		(((t_token *)(tmp->next->content))->token[0] == '\0'))
	{
		tmpo->fnf++;
		tmpo->err++;
		tmpo->file_msg = ft_strdup(((t_token *)(tmp->next->content))->token);
	}
	else if (tmpo->err == 0)
	{
		if (tmpo->fdout != 0)
			close(tmpo->fdout);
		tmpo->fdout = open(((t_token *)(tmp->next->content))->token, \
			O_CREAT | O_WRONLY | i, 0655);
		if (errno == 13 || tmpo->fdout == -1)
			for_aide(tmp, tmpo, 2, 12);
	}
	return (1);
}

void	init(t_fd **tmpo, t_list *tmp)
{
	if (tmp != NULL)
	{
		(*tmpo) = (t_fd *)malloc(sizeof(t_fd));
		(*tmpo)->file_msg = NULL;
		(*tmpo)->amb_msg = NULL;
		(*tmpo)->append = 0;
		(*tmpo)->fdin = 0;
		(*tmpo)->fdout = 0;
		(*tmpo)->heredoc_in = 0;
		(*tmpo)->heredoc_out = 0;
		(*tmpo)->err = 0;
		(*tmpo)->h_t_n = 0;
		(*tmpo)->r_t_n = 0;
		(*tmpo)->amb = 0;
		(*tmpo)->isd = 0;
		(*tmpo)->fnf = 0;
		(*tmpo)->pd = 0;
	}
}

void	redirections(t_data *data, t_list *t, int *e, t_fd	*tmpo)
{
	init(&tmpo, t);
	while (t)
	{
		ambiguous_handling(t, tmpo, e);
		if (((t_token *)(t->content))->e_token_id == READ && \
			((t_token *)(t->next->content))->amb == 0)
			help(t, e, tmpo);
		if (((t_token *)(t->content))->e_token_id == WRITE && \
			((t_token *)(t->next->content))->amb == 0 && (t->next != NULL))
			utils(t, O_TRUNC, tmpo);
		if (((t_token *)(t->content))->e_token_id == APPEND && \
			((t_token *)(t->next->content))->amb == 0 && (t->next != NULL))
			utils(t, O_APPEND, tmpo);
		if ((((t_token *)(t->content))->e_token_id == PIPE) || t->next == NULL)
		{
			if (data->pipe++ == 0)
				data->fd = ft_lstnew((void *)tmpo);
			else
				ft_lstadd_back(&data->fd, ft_lstnew((void *)tmpo));
			init(&tmpo, t->next);
		}
		t = t->next;
	}
}
