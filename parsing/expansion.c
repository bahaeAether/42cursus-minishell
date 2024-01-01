/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:35:21 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:53:46 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

static	char	*utils(char *tmp1, char *tok, int j, char *tmp)
{
	char	*tmpo;
	char	*tmpoo;

	tmp1 = ft_substr(tok, 0, (j - 1));
	tmpo = tmp;
	tmpoo = tmp1;
	tok = ft_strjoin(tmp1, tmp);
	free(tmpo);
	free(tmpoo);
	return (tok);
}

static	char	*help(t_list *token, char *tok, size_t *i, size_t j)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp = ft_substr(tok, j, ((*i) - j));
	((t_token *)(token->content))->expand_start = (int)(j - 1);
	((t_token *)(token->content))->expand_end = (int)((*i) - j);
	tmp1 = tmp;
	tmp2 = ft_strdup(&tok[*i]);
	tmp = find_in_2d(tmp, tmp2, 0, 0);
	(*i) = (j);
	if (((t_token *)(token->previous)) && \
		((t_token *)(token->previous->content))->e_token_id != WORD && \
			((t_token *)(token->previous->content))->e_token_id != PIPE)
	{
		((t_token *)(token->content))->amb_msg = ft_strdup(tmp);
		if (tmp[0] == '\0')
			((t_token *)(token->content))->amb++;
		if (check_for_char(tmp, ' ') != 0 || check_for_char(tmp, '\t') != 0 \
			|| check_for_char(tmp, '\n') != 0)
			((t_token *)(token->content))->amb++;
	}
	((t_token *)(token->content))->expand_len = ft_strlen(tmp);
	update_meta(token, ft_strlen(tmp));
	return (utils(tmp1, tok, j, tmp));
}

static	char	*exit_status(char *tok, int i)
{
	char	*head;
	char	*taile;
	char	*status;
	char	*tmp;
	char	*tmpo;

	tmp = tok;
	head = ft_substr(tok, 0, i);
	taile = ft_substr(tok, (i + 2), ((int)ft_strlen(tok) - (i + 1)));
	free(tmp);
	tmp = head;
	if (g_global.status == 255)
		g_global.status = 0;
	status = ft_itoa(g_global.status);
	tmpo = status;
	tok = ft_strjoin(head, status);
	free(tmp);
	free(tmpo);
	tmp = tok;
	tmpo = taile;
	tok = ft_strjoin(tok, taile);
	free(tmp);
	free(tmpo);
	return (tok);
}

static	void	help_pls(char *tok, size_t *i, int *j, int *y)
{
	(*i)++;
	(*y)++;
	(*j) = (*i);
	if (tok[*i] != '*' && ft_isalnum(tok[(*i)]) != 1)
	{
		while (tok[(*i)] && \
			(ft_isalpha(tok[(*i)]) == 1 || ft_isalnum(tok[(*i)]) == 1 || \
				tok[(*i)] == '_'))
			(*i)++;
	}
	else
		(*i)++;
}

char	*parameter_expansion(t_list *token, size_t i, int j, int y)
{
	char	*tok;
	char	*tmpo;

	tok = ((t_token *)(token->content))->token;
	while (ft_strlen(tok) > i && tok[i])
	{
		if (tok[i] == '$' && ((t_token *)(token->content))->expand[y] == '1' \
			&& tok[i + 1] == '?')
			tok = exit_status(tok, i);
		else if (tok[i] == '$' && ((t_token *)(token->content))->expand[y] == \
			'1' && (tok[i + 1] == '_' || ft_isalpha(tok[i + 1]) == 1 || \
				ft_isalnum(tok[i + 1]) == 1 || tok[i + 1] == '*'))
		{
			help_pls(tok, &i, &j, &y);
			tmpo = tok;
			tok = help(token, tok, &i, j);
			free(tmpo);
		}
		if (ft_strlen(tok) > i && tok[i])
			i++;
	}
	return (tok);
}
