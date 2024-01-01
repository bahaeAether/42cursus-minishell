/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:35:09 by hnaama            #+#    #+#             */
/*   Updated: 2023/02/03 20:35:59 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	b_str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*b_str_join(char *stash, char *buffer)
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
	len = b_str_len(stash) + b_str_len(buffer) + 1;
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

char	*b_str_dup(char *s1)
{
	char	*p;
	size_t	i;

	i = b_str_len (s1) * sizeof(char);
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
