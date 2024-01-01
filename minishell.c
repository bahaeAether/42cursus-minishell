/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:55:48 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/28 21:25:10 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

void	crt_c(int sig)
{
	if (sig == SIGINT)
	{
		g_global.status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_abs(int c)
{
	if (c < 0)
		return (-c);
	return (c);
}

char	**envp(char **env)
{
	char	**envp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	envp = (char **)malloc((sizeof(char *) * (i + 1)));
	i = 0;
	while (env[i])
	{
		envp[i] = ft_strdup(env[i]);
		i++;
	}
	envp[i] = 0;
	return (envp);
}

static	void	ini(t_data *data)
{
	g_global.heredoc_c = 0;
	data->pipe = 0;
	data->token_count = 0;
	data->promt = readline("minishell>");
}

int	main(int ac, char **dc, char **env)
{
	t_data	*data;

	(void) ac;
	(void) dc;
	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	g_global.envp = envp(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, crt_c);
	while (1)
	{
		ultimate_free(data);
		ini(data);
		if (data->promt == NULL)
		{
			ultimate_free(data);
			exit(g_global.status);
		}
		if (data->promt && data->promt[0] != '\0')
		{
			add_history(data->promt);
			parsing(data);
			if (data && data->cmd && data->f == 0)
				execution(data->cmd, &g_global.envp);
		}
	}
}

			// t_node *tmp = data->cmd;
			// int i = 0;
			// while (tmp)
			// {
			// 	printf("cmd%s\n", tmp->cmd);
			// 	while (tmp->args[i])
			// 	{
			// 		printf("ergs[%d]%s\n",i , tmp->args[i]);
			// 		i++;
			// 	}
			// 	i = 0;
			// 	printf("pipe %d\n", tmp->pipe);
			// 	printf("input_redir %d\n", tmp->input_redir);
			// 	printf("output_redir %d\n", tmp->output_redir);
			// 	printf("append_redir %d\n", tmp->append_redir);
			// 	printf("here_doc %d\n", tmp->here_doc);
			// 	printf("amb %d\n", tmp->amb);
			// 	printf("amb_msg %s\n", tmp->amb_msg);
			// 	printf("isd %d\n", tmp->isd);
			// 	printf("cmd_not_found %d\n", tmp->cmd_not_found);
			// 	printf("file_not_found %d\n", tmp->file_not_found);
			// 	tmp = tmp->next;
			// }