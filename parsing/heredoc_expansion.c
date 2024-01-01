/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:56:23 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:54:38 by baboulou         ###   ########.fr       */
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

static	char	*help(char *tok, int i, int j)
{
	char	*tmp;
	char	*tmpo;
	char	*tmp1;

	tmp1 = NULL;
	tmp = ft_substr(tok, j, (i - j));
	tmp = find_in_2d(tmp, ft_strdup(&tok[i]), 0, 0);
	tmpo = utils(tmp1, tok, j, tmp);
	return (tmpo);
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
			(ft_isalpha(tok[(*i)]) == 1 || ft_isalnum(tok[(*i)]) == 1))
			(*i)++;
	}
	else
		(*i)++;
}

char	*heredoc_expansion(char *token, size_t i, int j, int y)
{
	char	*tok;
	char	*tmpo;

	tok = token;
	while (ft_strlen(tok) > i && tok[i])
	{
		if (tok[i] == '$' && tok[i + 1] == '?')
			tok = exit_status(tok, i);
		else if (tok[i] == '$' && (tok[i + 1] == '_' || \
			ft_isalpha(tok[i + 1]) == 1))
		{
			help_pls(tok, &i, &j, &y);
			tmpo = tok;
			tok = help(tok, i, j);
			free(tmpo);
		}
		if (ft_strlen(tok) > i && tok[i] && tok[i] == '$')
			y++;
		if (ft_strlen(tok) > i && tok[i])
			i++;
	}
	return (tok);
}
