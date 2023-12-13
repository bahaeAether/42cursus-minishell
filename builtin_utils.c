/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahae <bahae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:59:52 by bahae             #+#    #+#             */
/*   Updated: 2023/12/13 11:13:20 by bahae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

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

void	fill_struct(t_env *envp, char *str)
{
	int	n;
	int	i;

	n = len_until_equal(str);
	envp->key = malloc(n + 1);
	i = -1;
	while (++i < n)
		envp->key[i] = str[i];
	envp->key[i] = 0;
	envp->value = malloc();
	n = 0;
	while (str[++i])
		envp->value[n++] = str[i];
	envp->value[n] = 0;
	envp->next = 0;
}

t_env	*ft_char_to_list(char **envp)
{
	t_env	*new_envp;
	t_env	*tmp_envp;
	int		n;
	int		i;

	n = ft_array_len(envp);
	if (!n)
		return (0);
	new_envp = malloc(sizeof(t_env));
	tmp_envp = new_envp;
	fill_struct(tmp_envp, envp[0]);
	i = 1;
	while (i < n)
	{
		tmp_envp->next = malloc(sizeof(t_env));
		tmp_envp = tmp_envp->next;
		fill_struct(tmp_envp, envp[i]);
	}
	return (new_envp);
}
