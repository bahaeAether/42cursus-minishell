/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:24:43 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/27 11:47:19 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "?=", 2) && ft_strncmp(envp[i], "_=", 2)
			&& ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}
