/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:56:11 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:56:32 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char )c)
			return ((char *)s + i);
		i++;
	}
	if ((char )c == '\0')
		return ((char *)s + i);
	return (0);
}
