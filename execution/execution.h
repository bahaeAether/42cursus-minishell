/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:00:21 by baboulou          #+#    #+#             */
/*   Updated: 2023/11/01 11:00:21 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H
# define GETCWD_1 "bash: cd: error retrieving current directory: "
# define GETCWD_2 "getcwd: cannot access parent directories: "
# define GETCWD_3 "No such file or directory\n"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../parsing/parsing.h"

typedef struct s_node	t_node;
typedef struct s_data	t_data;
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_global
{
	int				status;
	int				heredoc_c;
	char			**envp;
}		t_global;

typedef struct s_fd_recall
{
	int	new_stdin;
	int	new_stdout;
}		t_fd_recall;

/*	builtins	*/

int			ft_echo(char **args);
int			ft_cd(char **args, char ***envp);
int			ft_pwd(char **envp);
int			ft_export(char **args, char ***envp);
int			ft_unset(char **args, char ***envp);
int			ft_env(char **envp);
int			ft_exit(char **args);
int			print_permission_msg(t_node *node);
int			len_until_equal(char *str);
int			ft_array_len(char **array);
int			*sort_env(char **envp);
int			handle_echo_option(char *str);
int			special_cd(char *label, char ***envp);
int			str_is_numeric(char *str);
int			ft_is_valid(char *str);
int			reset_env_variable(char **envp, char *str);
int			no_arg_export(char **envp);
int			ft_unset_is_valid(char *str);
int			ft_str_in_vector(char *str, char **envp);
int			check_end(char *envp, char *str);
int			print_export_error(char *str);
int			print_nofd_error_and_free(char *dir, char *cwd, char *arg);
int			ft_min(int a, int b);
void		ft_add_str_to_array(char ***envp, char *str);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
void		print_nofd_error(char *dir);
char		*ft_get_env_value(char *key, char **envp);
void		setup_pwds(char ***envp, char *pwd);
void		unset_env_variable(char ***envp, char *str);
t_env		*parse_sorted_env(char **envp);

/*	execution	*/

t_fd_recall	redirection_builtin(t_node *node);
t_fd_recall	setup_and_exec_builtin(t_node *node, char ***envp);
int			ft_is_builtin(char *cmd);
int			exec_builtin(t_node *node, char ***envp);
int			print_amb_msg(t_node *node);
int			print_file_not_found_msg(t_node *node);
int			print_cmd_not_found_msg(t_node *node);
int			print_isd_msg(t_node *node);
void		redirection(t_node *node);
void		ft_pipe_setup(t_node *node, int *fd);
void		ft_close(t_node *node);
void		execution(t_node *node, char ***envp);
void		modify_fd(t_node *node, t_fd_recall *recall);
void		ft_close_builtin(t_node *node, t_fd_recall recall);

#endif
