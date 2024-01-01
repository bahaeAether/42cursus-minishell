/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:31:10 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/29 22:41:11 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

int	special_cd(char *label, char ***envp)
{
	char	*dir;

	dir = ft_get_env_value(label, *envp);
	if (!dir)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(label, 2);
		ft_putstr_fd(" not set\n", 2);
		return (1);
	}
	if (chdir(dir) == -1)
	{
		print_nofd_error(dir);
		free(dir);
		return (1);
	}
	setup_pwds(envp, dir);
	free(dir);
	return (0);
}

char	*backup_pwd(char ***envp, char *used_pwd)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;
	char	*tmp2;

	oldpwd = ft_get_env_value("PWD", *envp);
	tmp = ft_strjoin(oldpwd, "/");
	free(oldpwd);
	if (used_pwd[ft_strlen(used_pwd) - 1] == '/')
	{
		tmp2 = ft_substr(used_pwd, 0, ft_strlen(used_pwd) - 1);
		pwd = ft_strjoin(tmp, tmp2);
		free(tmp2);
	}
	else
		pwd = ft_strjoin(tmp, used_pwd);
	free(tmp);
	return (pwd);
}

void	setup_pwds(char ***envp, char *used_pwd)
{
	char	*pwd_export[3];
	char	*pwd;
	char	*tmp;

	tmp = ft_get_env_value("PWD", *envp);
	pwd_export[0] = "export";
	pwd_export[1] = ft_strjoin("OLDPWD=", tmp);
	pwd_export[2] = NULL;
	free(tmp);
	ft_export(pwd_export, envp);
	free(pwd_export[1]);
	pwd = getcwd(NULL, 1024);
	if (!pwd)
		pwd = backup_pwd(envp, used_pwd);
	pwd_export[1] = ft_strjoin("PWD=", pwd);
	ft_export(pwd_export, envp);
	free(pwd_export[1]);
	free(pwd);
}

int	print_cwd_error_and_free(char *dir)
{
	ft_putstr_fd("bash: cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	free(dir);
	return (1);
}

int	ft_cd(char **args, char ***envp)
{
	char	*dir;
	char	*cwd;

	if (!args[1] || (args[1] && !args[1][0]))
		return (special_cd("HOME", envp));
	dir = ft_strdup(args[1]);
	cwd = getcwd(NULL, 1024);
	if (!cwd && !access(dir, F_OK))
	{
		setup_pwds(envp, dir);
		return (print_cwd_error_and_free(dir));
	}
	if (chdir(dir) == -1)
		return (print_nofd_error_and_free(dir, cwd, args[1]));
	setup_pwds(envp, dir);
	free(dir);
	if (cwd)
		free(cwd);
	return (0);
}
