/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:16:58 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:59:02 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	help(const char *s, int *i)
{
	if (s[(*i) + 1] == 'n')
	{
		write(1, "\n", 1);
		(*i)++;
	}
	else
		(*i)++;
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	arg;

	i = 0;
	va_start(arg, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			not_per(arg, s, (i + 1));
			i++;
		}
		else if (s[i] == 92)
			help(s, &i);
		else if (s[i] != '%')
			write(1, &s[i], 1);
		if (s[i])
			i++;
	}
	va_end(arg);
	return (i);
}
