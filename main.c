#include "execution.h"

void	redirection(t_node *node)
{
	if (node->input_redir)
	{
		dup2(node->input_redir, 0);
		close(node->input_redir);
	}
	if (node->output_redir)
	{
		dup2(node->output_redir, 1);
		close(node->output_redir);
	}
	if (node->append_redir)
	{
		dup2(node->append_redir, 1);
		close(node->append_redir);
	}
	if (node->here_doc)
	{
		dup2(node->here_doc, 0);
		close(node->here_doc);
	}
}

void	ft_pipe_setup(t_node *node)
{
	int	fd[2];

	pipe(fd);
	if (node->output_redir)
		close(node->output_redir);
	node->output_redir = fd[1];
	if (!node->next->input_redir)
		node->next->input_redir = fd[0];
	else
		close(fd[0]);
}

int	ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))l
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (2);
	if (!ft_strcmp(cmd, "pwd"))
		return (3);
	if (!ft_strcmp(cmd, "export"))
		return (4);
	if (!ft_strcmp(cmd, "unset"))
		return (5);
	if (!ft_strcmp(cmd, "env"))
		return (6);
	if (!ft_strcmp(cmd, "exit"))
		return (7);
	return (0);
}

void	ft_close(t_node *node)
{
	if (node->input_redir)
		close(node->input_redir);
	if (node->output_redir)
		close(node->output_redir);
	if (node->append_redir)
		close(node->append_redir);
	if (node->here_doc)
		close(node->here_doc);
}

void	exec_builtin(t_node *node, char **envp)
{
	if (ft_is_builtin(node->cmd) == 1)
		ft_echo(node->args);
	else if (ft_is_builtin(node->cmd) == 2)
		ft_cd(node->args);
	else if (ft_is_builtin(node->cmd) == 3)
		ft_pwd();
	else if (ft_is_builtin(node->cmd) == 4)
		ft_export(node->args, envp);
	else if (ft_is_builtin(node->cmd) == 5)
		ft_unset(node->args, envp);
	else if (ft_is_builtin(node->cmd) == 6)
		ft_env(envp);
	else if (ft_is_builtin(node->cmd) == 7)
		ft_exit(node->args);
}

void	set_exit_status(int status, char **envp)
{
	// char	*str;

	// str = ft_itoa(status);
	// ft_export(ft_add_str_to_array(envp, "_"), str);
	// free(str);
	printf("status: %d\n", status);
}

void	exec_commands(t_node *node, char **envp)
{
	int				pid;
	static int status;

	if (node->pipe)
		ft_pipe_setup(node);
	if (ft_is_builtin(node->cmd))
	{
		redirection(node);
		exec_builtin(node, envp);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			redirection(node);
			execve(node->cmd, node->args, envp);
			exit(1);
		}
	}
	ft_close(node);
	if (node->next)
		exec_commands(node->next, envp);
	if (!ft_is_builtin(node->cmd) && waitpid(pid, &status, 0) > 0)
	{
		while (waitpid(-1, NULL, 0) > 0);
		if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status), envp);
		if (WIFSIGNALED(status))
			set_exit_status(WTERMSIG(status) + 128, envp);
	}
}

void	execution(t_node *node, char **envp)
{
	int	status = 512;
	exec_commands(node, envp);
	// while (waitpid(-1, &status, 0) > 0);
	// printf("status: %d\n", WEXITSTATUS(status));
}

void	handler(int sig)
{
	if (sig == SIGQUIT)
		printf("Quit:\n");
	if (sig == SIGINT)
		printf("Interrupt:\n");
}

int main(int argc, char **argv, char **envp)
{
	t_node	*node;

	signal(SIGQUIT, handler);
	signal(SIGINT, handler);

	node = malloc(sizeof(t_node));
	node->cmd = "/usr/bin/ls";
	node->args = malloc(sizeof(char *) * 2);
	node->args[0] = node->cmd;
	node->args[1] = NULL;
	node->input_redir = 0;
	node->output_redir = 0;
	node->append_redir = 0;
	node->here_doc = 0;
	node->pipe = 1;

	node->next = NULL;


	// node->next = malloc(sizeof(t_node));
	// node->next->cmd = "/usr/bin/grep";
	// node->next->args = malloc(sizeof(char *) * 3);
	// node->next->args[0] = node->next->cmd;
	// node->next->args[1] = "this";
	// node->next->args[2] = NULL;
	// node->next->input_redir = 0;
	// node->next->output_redir = 0;
	// node->next->append_redir = 0;
	// node->next->here_doc = 0;
	// node->next->pipe = 1;

	// // node->next->next = NULL;


	// node->next->next = malloc(sizeof(t_node));
	// node->next->next->cmd = "/usr/bin/grep";
	// node->next->next->args = malloc(sizeof(char *) * 3);
	// node->next->next->args[0] = node->next->next->cmd;
	// node->next->next->args[1] = "line";
	// node->next->next->args[2] = NULL;
	// node->next->next->input_redir = 0;
	// node->next->next->output_redir = 0;
	// node->next->next->append_redir = 0;
	// node->next->next->here_doc = 0;
	// node->next->next->pipe = 0;

	// node->next->next->next = NULL;


	execution(node, NULL);

	// int i = 512;

	// waitpid(-1, &i, 0);
	// printf("status: %d\n", WEXITSTATUS(i));
	return (0);
}
