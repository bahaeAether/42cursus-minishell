/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:03:11 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:05:32 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

void	should_expand(t_list *token, int i, int j)
{
	char	*tmp;

	tmp = ((t_token *)(token->content))->token;
	while (tmp[++i])
	{
		if (tmp[i] == '$')
			j++;
	}
	((t_token *)(token->content))->expand = (char *) \
		malloc(sizeof(char) * (j + 1));
	((t_token *)(token->content))->expand[j] = '\0';
	i = -1;
	j = 0;
	while (tmp[++i])
	{
		if (tmp[i] == '$')
		{
			if (((t_token *)(token->content))->token_meta[i] != 'q')
				((t_token *)(token->content))->expand[j] = '1';
			else
				((t_token *)(token->content))->expand[j] = '0';
			j++;
		}
	}
}

static void	normmmi(t_list *token, int *len)
{
	(*len)++;
	while (((t_token *)(token->content))->token[*len] && \
		((t_token *)(token->content))->token[*len] != '\'')
	{
		((t_token *)(token->content))->token_meta[*len] = 'q';
		(*len)++;
	}
}

void	update_meta_all(t_list *token, int len)
{
	while (((t_token *)(token->content))->token[len])
	{
		if (((t_token *)(token->content))->token[len] != '\'' \
			&& ((t_token *)(token->content))->token[len] != '"')
			((t_token *)(token->content))->token_meta[len] = 'u';
		else if (((t_token *)(token->content))->token[len] == '\'')
			normmmi(token, &len);
		else if (((t_token *)(token->content))->token[len] == '"')
		{
			len++;
			while (((t_token *)(token->content))->token[len] && \
				((t_token *)(token->content))->token[len] != '"')
			{
				((t_token *)(token->content))->token_meta[len] = 'Q';
				len++;
			}
		}
		if (((t_token *)(token->content))->token[len])
			len++;
	}
}

void	update_meta(t_list *token, int len)
{
	if (((t_token *)(token->content))->token_meta[((t_token *) \
		(token->content))->expand_start] == 'u')
		str_filer(token, len, 'u');
	else if (((t_token *)(token->content))->token_meta[((t_token *) \
		(token->content))->expand_start] == 'q' || \
			((t_token *)(token->content))->token_meta[((t_token *) \
				(token->content))->expand_start] == 's')
		str_filer(token, len, 'q');
	else if (((t_token *)(token->content))->token_meta[((t_token *) \
		(token->content))->expand_start] == 'd' || \
			((t_token *)(token->content))->token_meta[((t_token *) \
				(token->content))->expand_start] == 'Q')
		str_filer(token, len, 'Q');
}

int	check_for_char(char *str, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}
