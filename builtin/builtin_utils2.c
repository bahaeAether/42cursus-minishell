/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:48:28 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/29 15:04:29 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i])
			&& str[i] != '_' && str[i] != '=')
			return (0);
		if (str[i] == '=')
			return (1);
	}
	return (1);
}

void	print_nofd_error(char *dir)
{
	if (!opendir(dir))
	{
		ft_putstr_fd("bash: cd: ", 2);
		perror(dir);
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

int	print_nofd_error_and_free(char *dir, char *cwd, char *arg)
{
	print_nofd_error(arg);
	if (dir)
		free(dir);
	if (cwd)
		free(cwd);
	return (1);
}

int	print_export_error(char *str)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("' : not a valid identifier\n", 2);
	return (1);
}
