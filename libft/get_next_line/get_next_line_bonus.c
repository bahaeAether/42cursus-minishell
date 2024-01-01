/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:32:42 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/21 19:46:21 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	b_check_nl(char *stash)
{
	int	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	return (i);
}

void	b_fn( char **stash, char **buffer)
{
	char	*tmp;

	if (stash[0][b_check_nl(*stash)] == 10)
	{
		tmp = b_str_dup(*stash + (b_check_nl(*stash) + 1));
		stash[0][b_check_nl(*stash) + 1] = '\0';
		*buffer = b_str_dup(*stash);
		free(*stash);
		*stash = tmp;
		return ;
	}
	*buffer = *stash;
	*stash = NULL;
	if (b_str_len(*buffer) == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static	void	*b_my_free(char **to_free, char **to_free2)
{
	free(*to_free);
	*to_free = NULL;
	if (to_free2)
	{
		free(*to_free2);
		to_free = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash[FOPEN_MAX];
	ssize_t		read_ret;

	read_ret = 1;
	if (BUFFER_SIZE <= 0 && fd < 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	if (!stash[fd])
		stash[fd] = b_str_dup("");
	while (stash[fd][b_check_nl(stash[fd])] != 10 && read_ret != 0)
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (read_ret < 0)
			return (b_my_free(&(stash[fd]), &buffer));
		buffer[read_ret] = '\0';
		stash[fd] = b_str_join(stash[fd], buffer);
	}
	free(buffer);
	buffer = NULL;
	b_fn(&(stash[fd]), &buffer);
	return (buffer);
}
