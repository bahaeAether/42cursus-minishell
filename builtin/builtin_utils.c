/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:27:29 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/27 12:17:44 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	len_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	ft_add_str_to_array(char ***envp, char *str)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = malloc(sizeof(char *) * (ft_array_len(*envp) + 2));
	while ((*envp)[++i])
		tmp[i] = (*envp)[i];
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	free(*envp);
	*envp = tmp;
}

int	*sort_env(char **envp)
{
	int	i;
	int	j;
	int	tmp;
	int	*sorted;

	i = -1;
	sorted = malloc(sizeof(int) * (ft_array_len(envp) + 1));
	while (envp[++i])
		sorted[i] = i;
	i = -1;
	while (++i < ft_array_len(envp))
	{
		j = i;
		while (++j < ft_array_len(envp))
		{
			if (ft_strcmp(envp[sorted[i]], envp[sorted[j]]) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
		}
	}
	sorted[i] = -1;
	return (sorted);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst)
	{
		tmp = *lst;
		if (tmp)
		{
			while (tmp && tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			*lst = new;
	}
}
