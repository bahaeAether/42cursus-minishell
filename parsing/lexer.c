/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:07:47 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/29 19:52:25 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_global	g_global;

int	count_pipe(t_list *token_list)
{
	int		i;
	t_list	*tmp;

	i = 1;
	tmp = token_list;
	while (tmp)
	{
		if (((t_token *)(tmp->content))->e_token_id == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_split_inpho(t_data **data, t_list *token_list, int i, int j)
{
	t_list	*tmp;

	tmp = token_list;
	(*data)->split_info = (int *)ft_calloc(sizeof(int), \
		(count_pipe(token_list) + 1));
	while (tmp)
	{
		if (((t_token *)(tmp->content))->e_token_id == PIPE \
			|| tmp->next == NULL)
		{
			(*data)->split_info[j] = i;
			j++;
		}
		tmp = tmp->next;
		i++;
	}
}

static	void	help(t_node *cmd, t_list *tmp, int *j, t_list *tmpo)
{
	if (((t_token *)(tmp->content))->e_token_id == WORD && \
		((t_token *)(tmp->content))->token[0] != '\0')
	{
		if (((t_token *)(tmp->content))->e_token_id == WORD)
			cmd->args[*j] = ft_strdup(((t_token *)(tmp->content))->token);
		if ((*j) == 0)
		{
			if (((t_token *)(tmp->content))->e_token_id == WORD)
				cmd->cmd = ft_strdup(cmd->args[0]);
		}
		(*j)++;
	}
	cmd->input_redir = ((t_fd *)(tmpo->content))->fdin;
	cmd->output_redir = ((t_fd *)(tmpo->content))->fdout;
	cmd->append_redir = ((t_fd *)(tmpo->content))->append;
	if (((t_fd *)(tmpo->content))->h_t_n \
		>= ((t_fd *)(tmpo->content))->r_t_n)
		cmd->here_doc = ((t_fd *)(tmpo->content))->heredoc_out;
	else if (((t_fd *)(tmpo->content))->heredoc_out != 0)
		close(((t_fd *)(tmpo->content))->heredoc_out);
	fill_err_in_cmd(cmd, tmpo);
}

t_list	*helppp(t_list *tmp)
{
	t_list	*tmpo;

	if (((t_token *)(tmp->content))->e_token_id == WORD && \
		((t_token *)(tmp->content))->token[0] == '\0')
		tmpo = tmp->next;
	if (((t_token *)(tmp->content))->e_token_id != WORD)
		tmpo = tmp->next->next;
	else
		tmpo = tmp->next;
	return (tmpo);
}

void	fill_s_cmd(t_data **data, t_list *token_list, int i, int j)
{
	t_list	*tmp;
	t_list	*tmpo;
	t_node	*cmd;
	int		pre;

	pre = 0;
	tmp = token_list;
	tmpo = (*data)->fd;
	while (count_pipe(token_list) > i)
	{
		cmd = (t_node *)ft_calloc(sizeof(t_node), 1);
		cmd->args = (char **)ft_calloc(sizeof(char *), \
			(ft_abs(((*data)->split_info[i] - pre) + 1)));
		while (tmp && ((t_token *)(tmp->content))->e_token_id != PIPE)
		{
			help(cmd, tmp, &j, tmpo);
			tmp = helppp(tmp);
		}
		j = 0;
		if (tmp)
			tmp = tmp->next;
		tmpo = tmpo->next;
		add_cmd_node(*data, cmd);
		pre = (*data)->split_info[i++];
	}
}
