/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:52:17 by hnaama            #+#    #+#             */
/*   Updated: 2024/01/01 01:25:31 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define READLINE_LIBRARY

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include "../minishell.h"
# include "../libft/libft.h"
# include "../execution/execution.h"

/* change these paths to your readline paths */

# include "/Users/baboulou/readline/include/readline/readline.h"
# include "/Users/baboulou/readline/include/readline/history.h"
//# include "/nfs/homes/baboulou/readline/include/readline/readline.h"
//# include "/nfs/homes/baboulou/readline/include/readline/history.h"

typedef struct s_token
{
	char	*token;
	char	*token_meta;
	char	*expand;
	char	*amb_msg;
	char	*file_msg;
	int		expand_start;
	int		expand_end;
	int		expand_len;
	int		token_num;
	int		fdin;
	int		fdout;
	int		heredoc;
	int		eppend;
	int		amb;
	int		fnf;
	int		isd;
	enum
	{
		PIPE,
		WORD,
		READ,
		WRITE,
		APPEND,
		HEREDOC,
	} e_token_id;
}	t_token;

# ifndef T_NODE
#  define T_NODE

typedef struct s_node
{
	char			*cmd;
	char			**args;
	char			*amb_msg;
	char			*file_msg;
	int				pipe;
	int				input_redir;
	int				output_redir;
	int				append_redir;
	int				here_doc;
	int				amb;
	int				isd;
	int				cmd_not_found;
	int				file_not_found;
	int				pd;
	struct s_node	*next;
}	t_node;

# endif

typedef struct s_fd
{
	char	*file_msg;
	char	*amb_msg;
	int		fdin;
	int		fdout;
	int		append;
	int		heredoc_in;
	int		h_t_n;
	int		r_t_n;
	int		heredoc_out;
	int		err;
	int		amb;
	int		fnf;
	int		isd;
	int		pd;
}	t_fd;

typedef struct s_data
{
	int		i;
	int		c;
	int		e;
	int		f;
	int		pipe;
	int		path_exist;
	char	*tmp;
	char	**paths;
	char	*path;
	int		token_count;
	int		yes_or_no;
	char	*promt;
	char	*promt_meta;
	int		*split_info;
	t_node	*cmd;
	t_list	*tokens_list;
	t_list	*fd;
	t_token	token;
}	t_data;

char	*find_in_2d(char *tmp, char *finish, int i, int j);
void	free_t_node(t_node *cmd);
void	ambiguous_handling(t_list *tokens_list, t_fd *tmpo, int *e);
void	for_normstuff(t_list *tmp, t_fd *tmpo);
void	remove_first(t_list **token);
int		checks(int e, int isd, t_list *t);
void	free_token_node(t_list *token);
char	*make_eof(t_data *data, char *eof, int i, int j);
void	update_token(t_list **token, t_list *head);
void	ft_putstr_fd_next_n(int fd, t_list *tmp);
char	*heredoc_expansion(char *token, size_t i, int j, int y);
void	ft_split_inpho(t_data **data, t_list *token_list, int i, int j);
void	child(t_data *data, t_list *heredoc, t_list *fd);
void	ft_putstr_fd_n(char *str, int fd);
void	cmd_not_found(t_data *data, t_node *node);
void	update_meta_all(t_list *token, int len);
void	ultimate_free(t_data *data);
int		ifpath(char *str);
int		is_dir(char *str);
int		count_track(t_list *token_list);
int		enter_heredoc(char *eof, char *tmp);
void	crt_c(int sig);
void	check_abslut_path(t_node *cmd, int i);
int		check_for_char(char *str, int c);
int		ft_abs(int c);
int		len_without_quots(t_list *token);
void	free_tokens_list(t_list *tokens_list);
void	str_filer(t_list *token, int len, char c);
void	remove_re(t_list *tokens);
void	remove_quotes(t_list *token, int i, int j);
char	*free_infind(char *tmp, char *finish);
void	parsing(t_data *data);
void	make_promt_meta(t_data *data);
void	tokenizer(t_data **data, int i, int j);
void	heredoc(t_data *data, t_list *heredoc, t_list *fd, int *e);
void	redirections(t_data *data, t_list *tokens, int *e, t_fd *tmpo);
void	update_meta(t_list *token, int len);
void	print_token(t_list *tokens_list);
void	token_int_filler(t_token *tmp);
void	fill_err_in_cmd(t_node *cmd, t_list *tmpo);
void	make_cmd(t_node *cmd, t_data *data);
void	error_handling(t_list *tokens_list, t_data *data);
void	ft_putstr_fd_exit(char *str, int fd, int exist);
void	check_quotes(t_data *data, int *e);
char	*parameter_expansion(t_list *token, size_t i, int j, int y);
void	e_token_id_filler(t_list *tmp);
void	ft_putstr_fd_next(char *str, int fd, t_list *tmp);
void	should_expand(t_list *token, int i, int j);
void	add_cmd_node(t_data *lst, t_node *data);
void	fill_s_cmd(t_data **data, t_list *tokens_list, int i, int a);
void	free_cmd(t_node *cmd);

#endif
