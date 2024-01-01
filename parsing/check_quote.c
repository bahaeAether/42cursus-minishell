/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:19 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:54:06 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

char	*free_infind(char *tmp, char *finish)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = tmp;
	tmp2 = ft_strjoin(tmp, finish);
	free (tmp1);
	free (finish);
	return (tmp2);
}

int	len_without_quots(t_list *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (((t_token *)(token->content))->token[i])
	{
		if (((t_token *)(token->content))->token[i] == '"' && \
			((t_token *)(token->content))->token_meta[i] != 'q')
			j++;
		else if (((t_token *)(token->content))->token[i] == '\'' && \
			((t_token *)(token->content))->token_meta[i] != 'Q')
			j++;
		i++;
	}
	return (i - j);
}

void	remove_quotes(t_list *token, int i, int j)
{
	char	*tmp;
	char	*tmpo;

	tmp = ft_calloc((len_without_quots(token) + 1), sizeof(char));
	while (((t_token *)(token->content))->token[i])
	{
		if (((t_token *)(token->content))->token[i] == '"' && \
			((t_token *)(token->content))->token_meta[i] != 'q')
			i++;
		else if ((((t_token *)(token->content))->token[i] == '\'' && \
			((t_token *)(token->content))->token_meta[i] != 'Q'))
			i++;
		else
		{
			tmp[j++] = ((t_token *)(token->content))->token[i];
			i++;
		}
	}
	tmpo = ((t_token *)(token->content))->token;
	((t_token *)(token->content))->token = tmp;
	free(tmpo);
}

static	char	*help(t_data *data, char *tmp, char *eof, t_list *fd)
{
	if (tmp != NULL && (enter_heredoc(eof, tmp) == 0))
		exit (1);
	if (data->yes_or_no == 0)
		tmp = heredoc_expansion(tmp, 0, 0, 0);
	if (enter_heredoc(eof, tmp) != 0)
		ft_putstr_fd_n(tmp, ((t_fd *)(fd->content))->heredoc_in);
	return (tmp);
}

void	child(t_data *data, t_list *heredoc, t_list *fd)
{
	char	*tmp;
	char	*eof;

	signal(SIGINT, SIG_DFL);
	eof = make_eof(data, ((t_token *)(heredoc->next->content))->token, 0, 0);
	tmp = readline("heredoc>");
	if (tmp)
		tmp = help(data, tmp, eof, fd);
	while (tmp && enter_heredoc(eof, tmp) != 0)
	{
		free(tmp);
		tmp = readline("heredoc>");
		if (tmp != NULL && (enter_heredoc(eof, tmp) == 0))
			break ;
		if (tmp)
		{
			if (data->yes_or_no == 0)
				tmp = heredoc_expansion(tmp, 0, 0, 0);
			ft_putstr_fd_n(tmp, ((t_fd *)(fd->content))->heredoc_in);
		}
	}
	free(eof);
	close(((t_fd *)(fd->content))->heredoc_in);
	exit(1);
}
