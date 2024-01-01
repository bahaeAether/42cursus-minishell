/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 00:11:33 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:44:34 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*n_itoa(long n)
{
	char	*p;
	int		i;

	i = intlen(n);
	while (i > 0)
	{
		n *= -1;
		p = (char *)ft_calloc((i + 2), sizeof(char));
		if (!p)
			return (0);
		p[0] = '-';
		while (i > 0)
		{
			p[i] = (n % 10) + '0';
			n = n / 10;
			i--;
		}
	}
	return (p);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;

	i = intlen(n);
	if (n < 0)
		return (n_itoa(n));
	else
	{
		p = (char *)ft_calloc((i + 1), sizeof(char));
		if (!p)
		{
			return (0);
		}
		while (--i >= 0)
		{
			p[i] = (n % 10) + '0';
			n = n / 10;
		}
		return (p);
	}
}
