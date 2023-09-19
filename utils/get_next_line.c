/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:37:44 by yhachami          #+#    #+#             */
/*   Updated: 2023/09/01 23:23:31 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_next(char *old)
{
	char	*next;
	int		i;
	int		x;

	if (!ft_strchr(old, '\n'))
	{
		free(old);
		return (NULL);
	}
	x = get_nl(old);
	next = (char *) malloc(ft_strlen(old + x) + 1);
	i = 0;
	while (old[x + i])
	{
		next[i] = old[x + i];
		i++;
	}
	next[i] = '\0';
	free(old);
	return (next);
}

char	*get_line(char *next)
{
	char	*line;
	int		i;

	if (!next)
		return (NULL);
	line = (char *) malloc(get_nl(next) + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (next[++i])
	{
		line[i] = next[i];
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
	}
	line[i] = '\0';
	return (line);
}

char	*read_line(int fd, char **next)
{
	char	*buf;
	int		l;

	buf = (char *) malloc(BUFFER_SIZE + 1);
	l = 1;
	while (l > 0)
	{
		l = read(fd, buf, BUFFER_SIZE);
		if (l <= 0)
			break ;
		buf[l] = '\0';
		*next = ft_strjoin(*next, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (**next)
		return (*next);
	free(*next);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*next[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!next[fd])
		next[fd] = (char *) ft_calloc(1, 1);
	next[fd] = read_line(fd, &next[fd]);
	line = get_line(next[fd]);
	next[fd] = save_next(next[fd]);
	return (line);
}
