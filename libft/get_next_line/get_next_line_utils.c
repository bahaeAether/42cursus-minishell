/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:29:33 by hnaama            #+#    #+#             */
/*   Updated: 2023/01/30 19:43:33 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*str_join(char *stash, char *buffer)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	len;

	i = -1;
	j = 0;
	if (!stash)
		return (NULL);
	if (!buffer)
		return (stash);
	len = str_len(stash) + str_len(buffer) + 1;
	p = (char *)malloc(len * sizeof(char));
	if (!p)
		return (NULL);
	while (stash[++i])
		p[i] = stash[i];
	free(stash);
	while (buffer[j])
	{
		p[i + j] = buffer[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}

char	*str_dup(char *s1)
{
	char	*p;
	size_t	i;

	i = str_len (s1) * sizeof(char);
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (0);
	while (i + 1 > 0)
	{
		p[i] = s1[i];
		i--;
	}
	return (p);
}
