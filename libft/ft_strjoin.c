/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:53:41 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:56:40 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	len;

	i = -1;
	j = -1;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)ft_calloc(len, sizeof(char));
	if (!p)
		return (NULL);
	if (s1)
	{
		while (s1[++i])
			p[i] = s1[i];
	}
	if (s2)
	{
		while (s2[++j])
			p[i + j] = s2[j];
	}
	return (p);
}
