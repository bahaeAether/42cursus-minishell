/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:23:59 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:44:34 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t j)
{
	char	*p;
	int		i;
	int		len;

	len = j;
	i = 0;
	if (!s)
		return (NULL);
	if (j >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (s[i] && len--)
	{
		p[i++] = s[start++];
	}
	p[i] = '\0';
	return (p);
}
