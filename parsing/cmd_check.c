/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:40:53 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 18:02:58 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

void	token_int_filler(t_token *tmp)
{
	tmp->expand_len = 0;
	tmp->expand_start = 0;
	tmp->fdin = 0;
	tmp->fdout = 0;
	tmp->heredoc = 0;
	tmp->eppend = 0;
	tmp->amb = 0;
	tmp->fnf = 0;
	tmp->isd = 0;
}

static	void	help(t_data *data, t_node *cmd)
{
	data->tmp = ft_strjoin(data->paths[data->i], cmd->cmd);
	if (access(data->tmp, F_OK) == 0)
		data->e++;
	if (access(data->tmp, X_OK) == 0)
	{
		data->c++;
		free(cmd->cmd);
		cmd->cmd = ft_strdup(data->tmp);
	}
	free(data->tmp);
}

int	checkcmd(t_data *data, t_node *cmd)
{
	char	*tmp;

	data->i = -1;
	data->c = 0;
	data->e = 0;
	if (check_for_char(cmd->cmd, '/'))
		check_abslut_path(cmd, 1);
	else
	{
		tmp = cmd->cmd;
		check_abslut_path(cmd, 0);
		cmd->cmd = ft_strjoin("/", cmd->cmd);
		free(tmp);
		if (data->path_exist != 0)
		{
			while (data->paths[++(data->i)] && data->c == 0)
				help(data, cmd);
		}
		cmd_not_found(data, cmd);
	}
	return (1);
}

void	here_parsing(t_data *data)
{
	data->i = 0;
	data->path_exist = 0;
	while (g_global.envp[data->i])
	{
		if (ifpath(g_global.envp[data->i]) == 1)
		{
			data->path = &g_global.envp[data->i][5];
			data->path_exist++;
		}
		data->i++;
	}
	if (data->path_exist != 0)
		data->paths = ft_split(data->path, ':');
}

void	make_cmd(t_node *cmd, t_data *data)
{
	here_parsing(data);
	checkcmd(data, cmd);
	if (data->path_exist != 0)
		my_free(data->paths);
}
