/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:28:47 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/21 19:45:56 by hnaama           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_nl(char *stash)
{
	int	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	return (i);
}

void	fn( char **stash, char **buffer)
{
	char	*tmp;

	if (stash[0][check_nl(*stash)] == 10)
	{
		tmp = str_dup(*stash + (check_nl(*stash) + 1));
		stash[0][check_nl(*stash) + 1] = '\0';
		*buffer = str_dup(*stash);
		free(*stash);
		*stash = tmp;
		return ;
	}
	*buffer = *stash;
	*stash = NULL;
	if (str_len(*buffer) == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static	void	*my_free(char **to_free, char **to_free2)
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
	static char	*stash;
	ssize_t		read_ret;

	read_ret = 1;
	if (BUFFER_SIZE <= 0 && fd < 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	if (!stash)
		stash = str_dup("");
	while (stash[check_nl(stash)] != 10 && read_ret != 0)
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (read_ret < 0)
			return (my_free(&stash, &buffer));
		buffer[read_ret] = '\0';
		stash = str_join(stash, buffer);
	}
	free(buffer);
	buffer = NULL;
	fn(&stash, &buffer);
	return (buffer);
}

// int main()
// {
// 	int fd = open("test", O_CREAT | O_RDONLY, 0644);
// 	char *t = get_next_line(fd);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		printf("%s", t);
// 		free(t);
// 		t = get_next_line(fd);
// 	}
// 	system("leaks a.out");
// }