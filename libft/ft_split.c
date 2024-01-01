/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:41 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:44:34 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

char	**my_free(char **arr)
{
	size_t	k;

	k = 0;
	while (arr[k])
	{
		free(arr[k]);
		k++;
	}
	free(arr);
	return (NULL);
}

static size_t	word_len(const char *s, char c, size_t *word_start)
{
	size_t	i;

	i = 0;
	while (s[*word_start] == c)
		(*word_start)++;
	while (s[*word_start] && s[*word_start] != c)
	{
		i++;
		(*word_start)++;
	}
	return (i);
}

static void	word_start(const char *s, char c, size_t *index)
{
	while (s[*index])
	{
		if (s[*index] == c)
			(*index)++;
		else
			return ;
	}
	return ;
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	k;
	size_t	j;
	size_t	tmp;
	size_t	wc;

	k = 0;
	j = 0;
	wc = word_count(s, c);
	arr = (char **)ft_calloc(wc + 1, sizeof(char *));
	if (!arr)
		return (0);
	while (k < wc)
	{
		word_start(s, c, &j);
		tmp = j;
		arr[k] = ft_substr(s, tmp, word_len(s, c, &j));
		if (!arr[k])
			return (my_free(arr));
		k++;
	}
	return (arr);
}
