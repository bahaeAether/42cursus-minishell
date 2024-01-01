/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bass.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 02:50:04 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:58:38 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_bass(unsigned int n, unsigned int bass, char *nbr)
{
	if (n >= bass)
	{
		ft_putnbr_bass(n / bass, bass, nbr);
		ft_putnbr_bass(n % bass, bass, nbr);
	}
	else
		ft_putchar(nbr[n]);
}

void	ft_putnbr_10(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr_10(n * (-1));
	}
	else if (n >= 10)
	{
		ft_putnbr_10(n / 10);
		ft_putnbr_10(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	ft_put_adresse(unsigned long n, unsigned long bass, char *nbr)
{
	if (n >= bass)
	{
		ft_put_adresse(n / bass, bass, nbr);
		ft_put_adresse(n % bass, bass, nbr);
	}
	else
		ft_putchar(nbr[n]);
}
