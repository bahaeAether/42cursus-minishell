#ifndef EXECUTION_H

# define EXECUTION_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_node 
{
	char	*cmd;
	char	**args;
	int		input_redir;// file descriptor for input redirection '<'
	int		output_redir;// file descriptor for output redirection '>'
	int		append_redir;// file descriptor for append redirection '>>'
	int		here_doc;// file descriptor for here document '<<'
	int		pipe;
	struct s_node	*next;
}			t_node;

void	redirection(t_node *node);
void	ft_pipe_setup(t_node *node);
void	exec_builtin(t_node *node, char **envp);
void	execution(t_node *node, char **envp);
void	ft_close(t_node *node);
void	exec_commands(t_node *node, char **envp);
void	ft_free(char **array);
char	*ft_strdup(const char *s1);
char	**ft_add_str_to_array(char **array, char *str);
int		ft_echo(char **args);
int		ft_cd(char **args);
int		ft_pwd(void);
int		ft_export(char **args, char **envp);
int		ft_unset(char **args, char **envp);
int		ft_env(char **envp);
int		ft_exit(char **args);
int		ft_is_builtin(char *cmd);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
