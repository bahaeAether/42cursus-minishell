/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:32:54 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/27 11:52:22 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

char	*get_env_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (ft_substr(str, i + 1, ft_strlen(str)));
	return (NULL);
}

t_env	*parse_sorted_env(char **envp)
{
	int		i;
	int		*sorted;
	t_env	*env;
	t_env	*tmp;

	i = 0;
	env = NULL;
	sorted = sort_env(envp);
	while (sorted[i] != -1)
	{
		tmp = malloc(sizeof(t_env));
		tmp->key = ft_substr(envp[sorted[i]], 0,
				len_until_equal(envp[sorted[i]]));
		tmp->value = get_env_value(envp[sorted[i]]);
		tmp->next = NULL;
		ft_lstadd_back_env(&env, tmp);
		i++;
	}
	free(sorted);
	return (env);
}

int	reset_env_variable(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], len_until_equal(str))
			&& check_end(envp[i], str))
		{
			if (str[len_until_equal(str)])
			{
				free(envp[i]);
				envp[i] = ft_strdup(str);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	no_arg_export(char **envp)
{
	t_env	*env;
	t_env	*tmp;

	env = parse_sorted_env(envp);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_"))
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return (0);
}

int	ft_export(char **args, char ***envp)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	if (!args[1])
		return (no_arg_export(*envp));
	while (args[++i])
	{
		if (ft_is_valid(args[i]))
		{
			if (!reset_env_variable(*envp, args[i]))
				ft_add_str_to_array(envp, args[i]);
		}
		else
			err = print_export_error(args[i]);
	}
	return (err);
}
