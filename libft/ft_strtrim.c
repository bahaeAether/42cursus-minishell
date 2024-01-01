/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:24:29 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:44:34 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_front(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	l_set;

	i = 0;
	j = 0;
	l_set = ft_strlen(set);
	while (s1[i])
	{
		while (j != l_set)
		{
			while (s1[i] == set[j])
			{
				i++;
				j = 0;
			}
			j++;
		}
		return (i);
	}
	return (i);
}

static size_t	check_end(const char *s1, const char *set)
{
	size_t	j;
	size_t	l_set;
	size_t	l;

	j = 0;
	l_set = ft_strlen(set);
	l = ft_strlen(s1);
	while (l != 0)
	{
		while (j != l_set)
		{
			while (s1[l - 1] == set[j])
			{
				l--;
				j = 0;
			}
			j++;
		}
		return (l);
	}
	return (l);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	return (ft_substr(s1, check_front(s1, set),
			check_end(s1, set) - check_front(s1, set)));
}
