/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 15:57:58 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:51:28 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

static	t_list	*stich_tokenlist(t_list *token, t_list *head)
{
	t_list	*tmp;

	tmp = token->next;
	token = head;
	while (head->next)
		head = head->next;
	if (tmp)
	{
		head->next = tmp;
		tmp->previous = head;
	}
	return (token);
}

static void	ft_make_token(t_list *token, int j, int i, t_list **head)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->token = ft_substr(((t_token *)(token->content))->token, j, (i - j));
	tmp->token_meta = ft_substr(((t_token *)(token->content))->token_meta, j, \
		(i - j));
	tmp->expand = NULL;
	tmp->amb_msg = NULL;
	tmp->file_msg = NULL;
	tmp->expand_len = 0;
	tmp->e_token_id = WORD;
	tmp->expand_start = 0;
	tmp->fdin = 0;
	tmp->fdout = 0;
	tmp->heredoc = 0;
	tmp->eppend = 0;
	tmp->amb = ((t_token *)(token->content))->amb;
	tmp->fnf = ((t_token *)(token->content))->fnf;
	tmp->isd = ((t_token *)(token->content))->isd;
	if (head == NULL)
		(*head) = ft_lstnew((void *)tmp);
	else
		ft_lstadd_back(&(*head), ft_lstnew((void *)tmp));
}

static	void	help(t_list *tmp, t_list **head, int i, int j)
{
	while (((t_token *)(tmp->content))->token[i])
	{
		if (((t_token *)(tmp->content))->token_meta[0] == 'u' && \
			((t_token *)(tmp->content))->token[i] != ' ' && \
			((t_token *)(tmp->content))->token[i] != '\t' && \
			((t_token *)(tmp->content))->token[i] != '\n')
		{
			j = i;
			while (((t_token *)(tmp->content))->token_meta[i] == 'u' && \
				((t_token *)(tmp->content))->token[i] && \
				((t_token *)(tmp->content))->token[i] != ' ' && \
				((t_token *)(tmp->content))->token[i] != '\t' && \
				((t_token *)(tmp->content))->token[i] != '\n')
				i++;
			ft_make_token(tmp, j, i, head);
		}
		if (((t_token *)(tmp->content))->token[i])
			i++;
	}
}

void	update_token(t_list **token, t_list *head)
{
	t_list	*tmp;
	t_list	*to_stitch;

	tmp = *token;
	while (tmp)
	{
		if ((check_for_char(((t_token *)(tmp->content))->token, ' ') != 0 || \
			check_for_char(((t_token *)(tmp->content))->token, '\t') != 0 || \
			check_for_char(((t_token *)(tmp->content))->token, '\n') != 0) \
			&& ((t_token *)(tmp->content))->expand_len != 0)
			help(tmp, &head, 0, 0);
		if (head != NULL)
		{
			to_stitch = stich_tokenlist(tmp, head);
			if (tmp == *token)
				*token = to_stitch;
			else if (tmp->previous)
				tmp->previous->next = to_stitch;
			tmp->next = NULL;
			free_tokens_list(tmp);
			tmp = to_stitch;
			head = NULL;
		}
		tmp = tmp->next;
	}
}
