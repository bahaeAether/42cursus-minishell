/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:02:32 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/27 11:46:03 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

int	ft_unset_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

int	ft_str_in_vector(char *str, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], len_until_equal(envp[i]))
			&& !str[len_until_equal(envp[i])])
			return (1);
		i++;
	}
	return (0);
}

void	unset_env_variable(char ***envp, char *str)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * (ft_array_len(*envp)));
	while ((*envp)[i])
	{
		if (!ft_strncmp(str, (*envp)[i], len_until_equal((*envp)[i])))
		{
			free((*envp)[i]);
			i++;
		}
		tmp[j] = (*envp)[i];
		if (!(*envp)[i])
			break ;
		i++;
		j++;
	}
	tmp[j] = NULL;
	free(*envp);
	*envp = tmp;
}

int	ft_unset(char **args, char ***envp)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args[++i])
	{
		if (!ft_unset_is_valid(args[i]))
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
			continue ;
		}
		if (ft_str_in_vector(args[i], *envp))
			unset_env_variable(envp, args[i]);
	}
	return (status);
}
