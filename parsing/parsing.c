/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:52:01 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:24:04 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

int	count_track(t_list *token_list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = token_list;
	while (tmp && ((t_token *)(tmp->content))->e_token_id != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_putstr_fd_next(char *str, int fd, t_list *tmp)
{
	ft_putstr_fd(str, fd);
	write(fd, "'", 1);
	ft_putstr_fd(((t_token *)(tmp->next->content))->token, fd);
	write(fd, "'", 1);
	write(fd, "\n", 1);
	g_global.status = 258;
}

void	ft_putstr_fd_next_n(int fd, t_list *tmp)
{
	write(fd, "bash: ", 7);
	ft_putstr_fd(((t_token *)(tmp->next->content))->token, fd);
}

int	check_meta(t_data *data, char *meta)
{
	int	i;

	i = 0;
	while (meta[i])
	{
		if (meta[i] != 'b')
			return (1);
		i++;
	}
	data->f++;
	return (0);
}

void	parsing(t_data *data)
{
	t_node	*tmp;

	make_promt_meta(data);
	data->tokens_list = NULL;
	tokenizer(&data, 0, 0);
	error_handling((data->tokens_list), data);
	check_meta(data, data->promt_meta);
	if (data->f == 0)
	{
		remove_re(data->tokens_list);
		update_token(&data->tokens_list, NULL);
		ft_split_inpho(&data, data->tokens_list, 1, 0);
		fill_s_cmd(&data, data->tokens_list, 0, 0);
		tmp = data->cmd;
		while (tmp)
		{
			if (ft_is_builtin(tmp->cmd) == 0)
				make_cmd(tmp, data);
			if (tmp->next)
				tmp->pipe = 1;
			tmp = tmp->next;
		}
	}
}
