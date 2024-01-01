/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:34:05 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:51:56 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

static	void	deal_with_quotes(t_data *data, char quote, int *i)
{
	if (quote == '"')
	{
		data->promt_meta[*i] = 'd';
		(*i)++;
		while (data->promt[*i] && data->promt[*i] != '"')
		{
			data->promt_meta[*i] = 'Q';
			(*i)++;
		}
		if (data->promt[*i])
			data->promt_meta[*i] = 'd';
	}
	if (quote == '\'')
	{
		data->promt_meta[*i] = 's';
		(*i)++;
		while (data->promt[*i] && data->promt[*i] != '\'')
		{
			data->promt_meta[*i] = 'q';
			(*i)++;
		}
		if (data->promt[*i])
			data->promt_meta[*i] = 's';
	}
}

void	make_promt_meta(t_data *data)
{
	int	i;

	i = 0;
	data->promt_meta = (char *)ft_calloc \
		(ft_strlen(data->promt) + 1, sizeof(char));
	while (data->promt[i])
	{
		if (data->promt[i] == '<')
			data->promt_meta[i] = 'r';
		else if (data->promt[i] == ' ' || data->promt[i] == '\n' \
			|| data->promt[i] == '\t')
			data->promt_meta[i] = 'b';
		else if (data->promt[i] == '>')
			data->promt_meta[i] = 'w';
		else if (data->promt[i] == '|')
			data->promt_meta[i] = 'p';
		else if (data->promt[i] == '"')
			deal_with_quotes(data, '"', &i);
		else if (data->promt[i] == '\'')
			deal_with_quotes(data, '\'', &i);
		else
			data->promt_meta[i] = 'u';
		if (data->promt[i])
			i++;
	}
}

void	make_token(t_data **data, int j, int i)
{
	t_token	*tmp;

	tmp = (t_token *)malloc(sizeof(t_token));
	tmp->token = ft_substr((*data)->promt, j, (i - j));
	tmp->token_meta = ft_substr((*data)->promt_meta, j, (i - j));
	tmp->amb_msg = NULL;
	tmp->expand = NULL;
	tmp->file_msg = NULL;
	token_int_filler(tmp);
	if ((*data)->token_count == 0)
	{
		(*data)->token_count++;
		tmp->token_num = (*data)->token_count;
		(*data)->tokens_list = ft_lstnew((void *)tmp);
	}
	else
	{
		(*data)->token_count++;
		tmp->token_num = (*data)->token_count;
		ft_lstadd_back(&(*data)->tokens_list, ft_lstnew((void *)tmp));
	}
}

static	void	helper(t_data **data, int *j, int *i)
{
	*j = *i;
	if ((*data)->promt_meta[*j] == 'p')
	{
		make_token(data, *j, ((*j) + 1));
		(*i)++;
	}
	else
	{
		while ((*data)->promt_meta[*i] && (*data)->promt_meta[*i] \
			== (*data)->promt_meta[*j] && ((*i) < ((*j) + 2)))
			(*i)++;
		make_token(data, *j, *i);
	}
}

void	tokenizer(t_data **data, int i, int j)
{
	while ((*data)->promt_meta[i])
	{
		if ((*data)->promt_meta[i] == 'b')
			i++;
		else if ((*data)->promt_meta[i] == 'u')
		{
			j = i;
			while ((*data)->promt_meta[i] && (*data)->promt_meta[i] != 'b' \
				&& (*data)->promt_meta[i] != 'p' && (*data)->promt_meta[i] != \
					'r' && (*data)->promt_meta[i] != 'w')
				i++;
			make_token(data, j, i);
		}
		else if ((*data)->promt_meta[i] == 'd' || (*data)->promt_meta[i] == 's')
		{
			j = i;
			while ((*data)->promt_meta[i] && (*data)->promt_meta[i] != 'b' \
				&& (*data)->promt_meta[i] != 'w' && \
				(*data)->promt_meta[i] != 'r' && (*data)->promt_meta[i] != 'p')
				i++;
			make_token(data, j, i);
		}
		else
			helper(data, &j, &i);
	}
}
