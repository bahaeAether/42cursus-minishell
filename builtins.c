#include "execution.h"

int	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!args[1] || (args[1] && !ft_strcmp(args[1], "-n")))
		printf("\n");
	return (0);
}

int	ft_cd(char **args)
{
	if (args[1])
	{
		if (chdir(args[1]) == -1)
			printf("cd: %s: %s\n", args[1], strerror(errno));
	}
	else
	{
		if (chdir(getenv("HOME")) == -1)
			printf("cd: %s\n", strerror(errno));
	}
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 1024);
	if (getcwd(pwd, 1024))
		printf("%s\n", pwd);
	else
		printf("pwd: %s\n", strerror(errno));
	free(pwd);
	return (0);
}

int	ft_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || !ft_is_alpha(str[i]) || str[i] != '_')
		return (0);
	while (str[++i])
	{
		if (!ft_is_alpha(str[i]) && !ft_is_digit(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
		if (str[i] == '=')
			return (1);
	}
	return (1);
}

int	len_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	no_arg_export(char **envp)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = 0;
		printf("declare -x ");
		while (envp[i][j] && envp[i][j] != '=')
			printf("%c", envp[i][j++]);
		if (envp[i][j] == '=')
		{
			printf("=\"");
			j++;
			while (envp[i][j])
				printf("%c", envp[i][j++]);
			printf("\"\n");
		}
		i++;
	}
	return (0);
}

int	ft_export(char **args, char **envp)
{
	int	i;
	int	j;
	int	err;

	i = 0;
	err = 0;
	if (!args[1])
		return (no_arg_export(envp));
	while (args[++i])
	{
		if (ft_is_valid(args[i]))
		{
			j = -1;
			while (envp[++j])
			{
				if (!ft_strncmp(args[i], envp[j], len_until_equal(args[i])))
				{
					free(envp[j]);
					envp[j] = ft_strdup(args[i]);
					break ;
				}
			}
			if (!envp[j])
				envp = ft_add_str_to_array(envp, args[i]);
		}
		else
		{
			printf("-bash: export: `%s': not a valid identifier\n", args[i]);
			err = 1;
		}
	}
	return (err);
}

int	ft_unset(char **args, char **envp)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (envp[j])
		{
			if (!ft_strncmp(args[i], envp[j], ft_strlen(args[i])))
			{
				free(envp[j]);
				while (envp[j + 1])
				{
					envp[j] = envp[j + 1];
					j++;
				}
				envp[j] = NULL;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		exit(0);
	else if (i == 2)
	{
		if (ft_is_valid(args[1]))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		else
			exit(ft_atoi(args[1]));
	}
	else
	{
		printf("exit\nminishell: exit: too many arguments\n");
		exit(1);
	}
}
