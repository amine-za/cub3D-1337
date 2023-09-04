/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:29:06 by azaghlou          #+#    #+#             */
/*   Updated: 2023/09/01 16:43:27 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Function that free an array
void	free_arr(char **ar)
{
	int	i;

	i = -1;
	while (ar[++i])
		free(ar[i]);
	free(ar);
}

// Function the return the lenght of the tallest line
int	tallest_line_length(char **map)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > x)
			x = ft_strlen(map[i]);
		i++;
	}
	return (x);
}

// Function that add a string to an array as a new argument
char	**arrjoin(char **ar, char *line, int size)
{
	char	**rtrn;
	int		i;
	int		j;

	i = -1;
	if (!line)
		return (ar);
	rtrn = ft_calloc(sizeof(char *), (size + 2));
	while (ar[++i])
		rtrn[i] = ft_calloc(1, ft_strlen(ar[i]) + 1);
	i = -1;
	while (ar[++i])
	{
		j = -1;
		while (ar[i][++j])
			rtrn[i][j] = ar[i][j];
	}
	rtrn[i] = ft_strdup(line);
	free_arr(ar);
	free(line);
	return (rtrn);
}

// i use this function to check if the first and the last line have a '0' char
int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
