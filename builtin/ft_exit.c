/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:25:21 by baboulou          #+#    #+#             */
/*   Updated: 2023/12/27 11:43:45 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

int	str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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
		if (!str_is_numeric(args[1]))
		{
			ft_putstr_fd("exit\nbash: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		else
			exit((unsigned char)ft_atoi(args[1]));
	}
	else
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
	return (1);
}
