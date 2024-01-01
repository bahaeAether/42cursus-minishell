/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:05:54 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/29 14:54:21 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

int	check_end(char *envp, char *str)
{
	int	min_len;

	min_len = ft_min(len_until_equal(envp), len_until_equal(str));
	if (envp[min_len] == '=' && !str[min_len])
		return (1);
	if (envp[min_len] == '=' && str[min_len] == '=')
		return (1);
	if (!envp[min_len] && str[min_len] == '=')
		return (1);
	if (!envp[min_len] && !str[min_len])
		return (1);
	return (0);
}

char	*ft_get_env_value(char *key, char **envp)
{
	int		i;
	char	*value;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(key, envp[i],
				len_until_equal(envp[i])) && !key[len_until_equal(envp[i])])
		{
			value = ft_substr(envp[i], len_until_equal(envp[i]) + 1,
					ft_strlen(envp[i]));
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	ft_pwd(char **envp)
{
	char	*pwd;
	char	*pwd2;

	pwd = getcwd(NULL, 1024);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		pwd2 = ft_get_env_value("PWD", envp);
		printf("%s\n", pwd2);
		free(pwd2);
	}
	return (0);
}
