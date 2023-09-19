/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:56:37 by yhachami          #+#    #+#             */
/*   Updated: 2023/09/01 23:23:34 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_nl(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\n')
			break ;
	return (i + 1);
}

int	ft_strlen(char *s)
{
	int	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *) malloc(len + 1);
	if (!str)
		return (0);
	i = -1;
	while (s1[++i])
		*str++ = s1[i];
	i = -1;
	while (s2[++i])
		*str++ = s2[i];
	*str = '\0';
	if (s1)
		free(s1);
	return (str - len);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return (s + i);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return (s + i);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char		*p;
	char		*str;
	size_t		len;

	if (count >= SIZE_MAX && size >= SIZE_MAX)
		return (0);
	len = count * size;
	p = (char *) malloc(len);
	if (p != NULL)
	{
		str = (char *)p;
		while (len-- > 0)
			*str++ = '\0';
	}
	return (p);
}
