/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:09:27 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 11:14:32 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

void	ft_putstr_fd_n(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
}

void	cmd_not_found(t_data *data, t_node *cmd)
{
	if (data->e == 0)
	{
		cmd->cmd_not_found++;
		g_global.status = 127;
	}
	else if (data->c == 0)
	{
		cmd->cmd_not_found++;
		g_global.status = 127;
	}
}

int	ifpath(char *str)
{
	char	*hold;
	int		i;

	i = 0;
	hold = "PATH=";
	while (str[i] && hold[i])
	{
		if (str[i] != hold[i])
			return (0);
		i++;
	}
	return (1);
}

void	check_abslut_path(t_node *cmd, int i)
{
	if (cmd->cmd && is_dir(cmd->cmd) == 1)
	{
		cmd->isd++;
		cmd->file_msg = ft_strdup(cmd->cmd);
	}
	else if (i == 1)
	{
		if (access(cmd->cmd, F_OK) != 0)
		{
			cmd->file_not_found++;
			cmd->file_msg = ft_strdup(cmd->cmd);
			g_global.status = 127;
		}
		if (access(cmd->cmd, X_OK) != 0)
		{
			cmd->cmd_not_found++;
			g_global.status = 126;
		}
	}
}

void	ambiguous_handling(t_list *tokens_list, t_fd *tmpo, int *e)
{
	if (tmpo->err == 0 && \
		(*e) == 0 && ((((t_token *)(tokens_list->content))->e_token_id \
		== READ || ((t_token *)(tokens_list->content))->e_token_id == WRITE || \
			((t_token *)(tokens_list->content))->e_token_id == APPEND)))
	{
		if (((t_token *)(tokens_list->next->content))->amb != 0 && (*e) == 0)
		{
			tmpo->amb = 1;
			tmpo->amb_msg = \
				ft_strdup(((t_token *)(tokens_list->next->content))->amb_msg);
			tmpo->err++;
		}
	}
}
