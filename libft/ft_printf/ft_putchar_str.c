/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:38:16 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:58:33 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	not_per(va_list arg, const char *s, int i)
{
	if (s[i] == 'c')
		ft_putchar((va_arg(arg, int)));
	else if (s[i] == 's')
		ft_putstr((va_arg(arg, char *)));
	else if (s[i] == 'p')
	{
		write(1, "0x", 2);
		ft_put_adresse((va_arg(arg, unsigned long)), 16, "0123456789abcdef");
	}
	else if (s[i] == 'd' || s[i] == 'i')
		ft_putnbr_10((va_arg(arg, int)));
	else if (s[i] == 'u')
		ft_putnbr_bass((va_arg(arg, int)), 10, "0123456789");
	else if (s[i] == 'x')
		ft_putnbr_bass((va_arg(arg, int)), 16, "0123456789absdef");
	else if (s[i] == 'X')
		ft_putnbr_bass((va_arg(arg, int)), 16, "0123456789ABCDEF");
	else if (s[i] == '%')
		write(1, "%", 1);
}
