/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:02:33 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/23 10:47:32 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

char		*get_next_line(int fd);
int			ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(char *s, int c);
int			get_nl(char *s);
void		*ft_calloc(size_t count, size_t size);

#endif
