/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:15:13 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:53:11 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

void	ft_putstr_fd_exit(char *str, int fd, int exist)
{
	ft_putstr_fd(str, fd);
	if (exist != 0)
		exit(exist);
}

static	void	help(t_list *token, char *start, char *filer, char *end)
{
	char	*tmp;
	char	*tmpo;
	char	*tmpoo;

	tmp = start;
	tmpo = filer;
	start = ft_strjoin(start, filer);
	free(tmp);
	free(tmpo);
	tmp = start;
	tmpo = end;
	tmpoo = ((t_token *)(token->content))->token_meta;
	((t_token *)(token->content))->token_meta = ft_strjoin(start, end);
	free(tmp);
	free(tmpo);
	free(tmpoo);
}

void	str_filer(t_list *token, int len, char c)
{
	char	*filer;
	char	*start;
	char	*end;
	int		i;

	i = 0;
	start = ft_substr(((t_token *)(token->content))->token_meta, 0, \
		((t_token *)(token->content))->expand_start);
	end = ft_substr(((t_token *)(token->content))->token_meta, ((t_token *) \
		(token->content))->expand_end, (ft_strlen(((t_token *) \
			(token->content))->token_meta - ((t_token *) \
				(token->content))->expand_end)));
	filer = (char *)malloc(len * sizeof(char));
	while (i < len)
	{
		filer[i] = c;
		i++;
	}
	help(token, start, filer, end);
}

void	e_token_id_filler(t_list *tmp)
{
	while (tmp)
	{
		if (((t_token *)(tmp->content))->token_meta[0] == 'p')
			((t_token *)(tmp->content))->e_token_id = PIPE;
		else if (((t_token *)(tmp->content))->token_meta[0] == 'w')
		{
			if (ft_strlen(((t_token *)(tmp->content))->token_meta) == 2)
				((t_token *)(tmp->content))->e_token_id = APPEND;
			else
				((t_token *)(tmp->content))->e_token_id = WRITE;
		}
		else if (((t_token *)(tmp->content))->token_meta[0] == 'r')
		{
			if (ft_strlen(((t_token *)(tmp->content))->token_meta) == 2)
				((t_token *)(tmp->content))->e_token_id = HEREDOC;
			else
				((t_token *)(tmp->content))->e_token_id = READ;
		}
		else
			((t_token *)(tmp->content))->e_token_id = WORD;
		tmp = tmp->next;
	}
}

void	check_quotes(t_data *data, int *e)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	j = 0;
	y = 0;
	while (data->promt_meta[i])
	{
		if (data->promt_meta[i] == 'd')
			j++;
		if (data->promt_meta[i] == 's')
			y++;
		i++;
	}
	if (*e == 0 && ((j % 2) != 0 || (y % 2) != 0))
	{
		ft_putstr_fd("syntax error: unclosed quotes\n", 2);
		g_global.status = 258;
		(*e)++;
	}
}
