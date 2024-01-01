/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:38:14 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:52:50 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

char	*find_in_2d(char *tmp, char *finish, int i, int j)
{
	char	*tmp1;

	tmp1 = tmp;
	tmp = ft_strjoin(tmp, "=");
	free(tmp1);
	while (g_global.envp[i])
	{
		if (j == 0 && ft_strncmp(g_global.envp[i], tmp, ft_strlen(tmp)) == 0)
		{
			j++;
			tmp1 = tmp;
			tmp = ft_substr(g_global.envp[i], ft_strlen(tmp), \
				(ft_strlen(g_global.envp[i]) - ft_strlen(tmp)));
			free(tmp1);
		}
		i++;
	}
	if (j != 0)
		return (free_infind(tmp, finish));
	else
	{
		free(tmp);
		return (finish);
	}
}

char	*make_eof(t_data *data, char *eof, int i, int j)
{
	char	*ret;

	data->yes_or_no = 0;
	while (eof[i++])
	{
		if (eof[i] == '"' || eof[i] == '\'')
			j++;
	}
	if (j != 0)
		data->yes_or_no++;
	ret = (char *)malloc(((ft_strlen(eof) - j) + 1) * sizeof(char));
	i = -1;
	j = 0;
	while (eof[++i])
	{
		if (eof[i] != '"' && eof[i] != '\'')
		{
			ret[j] = eof[i];
			j++;
		}
	}
	ret[j] = '\0';
	return (ret);
}

int	enter_heredoc(char *eof, char *tmp)
{
	if (eof[0] == '\0' && tmp[0] == '\0')
		return (0);
	else if (tmp[0] == '\0' || (ft_strlen(eof) != ft_strlen(tmp)))
		return (1);
	else
		return (ft_strncmp(tmp, eof, ft_strlen(eof)));
}

static	void	help(int p, t_list *fd)
{
	if (WIFSIGNALED(p) != 0)
	{
		g_global.status = (128 + WTERMSIG(p));
		if (g_global.status == 130)
			g_global.heredoc_c = 1;
	}
	close(((t_fd *)(fd->content))->heredoc_in);
	signal(SIGINT, crt_c);
}

void	heredoc(t_data *data, t_list *heredoc, t_list *fd, int *e)
{
	int		pipefd[2];
	int		pid;
	int		p;

	if ((*e) == 0 && ((t_token *)(heredoc->content))->e_token_id == HEREDOC \
		&& g_global.heredoc_c == 0)
	{
		if (((t_fd *)(fd->content))->heredoc_out != 0)
			close(((t_fd *)(fd->content))->heredoc_out);
		if ((*e) == 0 && pipe(pipefd) == -1)
		{
			ft_putstr_fd("something went wrong with pipe\n", 2);
			(*e)++;
		}
		((t_fd *)(fd->content))->heredoc_out = pipefd[0];
		((t_fd *)(fd->content))->heredoc_in = pipefd[1];
		((t_fd *)(fd->content))->h_t_n = \
			((t_token *)(heredoc->content))->token_num;
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			child(data, heredoc, fd);
		waitpid(pid, &p, 0);
		help(p, fd);
	}
}
