/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:40:01 by azaghlou          #+#    #+#             */
/*   Updated: 2023/08/23 10:56:29 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(char *s1)
{
	int		i;
	int		j;
	char	*s2;

	i = ft_strlen(s1);
	j = 0;
	s2 = malloc(sizeof(char) * i + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		s2[j] = s1[j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}
