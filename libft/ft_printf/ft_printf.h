/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:29:59 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:58:27 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *s, ...);
void	ft_putstr(char *s);
void	ft_putchar(char c);
void	ft_putnbr_bass(unsigned int n, unsigned int bass, char *nbr);
void	ft_put_adresse(unsigned long n, unsigned long bass, char *nbr);
void	ft_putnbr_10(int n);
void	not_per(va_list arg, const char *s, int i);

#endif
