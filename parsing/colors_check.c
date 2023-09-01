/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:14:00 by azaghlou          #+#    #+#             */
/*   Updated: 2023/09/01 16:20:41 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// A function that handle the case of comma while checking the rgb string
int	comma_condition(char *rgb, int *j, char *nbr, int *comma_nbr)
{
	if (rgb[0] == ',')
	{
		j[0] = 0;
		comma_nbr[0]++;
		if (comma_nbr[0] > 2)
			return (1);
		if (ft_atoi(nbr) > 255)
			return (1);
		ft_bzero(nbr, ft_strlen(nbr));
	}
	return (0);
}

/* A function that being called by the one below it and take colors code
as strings and convert them to int and count and return the final result
the color code				  										  */
unsigned int	color_code(char **ar)
{
	t_rgb	t;

	t.a = 255;
	t.r = ft_atoi(ar[0]);
	t.g = ft_atoi(ar[1]);
	t.b = ft_atoi(ar[2]);
	free_arr(ar);
	return (rgb2int(t));
}

// Take the rgb code as string and return the real color code
unsigned int	read_rgb(char *rgb)
{
	int		i;
	char	*pntr;
	int		comma_num;
	char	**ar;

	i = -1;
	calloc_the_array(&ar, rgb, &pntr);
	comma_num = 0;
	while (rgb[++i] && rgb[i] != '\n')
	{
		while (rgb[i + 1] && (rgb[i + 1] == ' ' || rgb[i + 1] == '\t'))
			i++;
		if (rgb[++i] == ',')
		{
			if (comma_num == 0)
				pntr = &ar[1][0];
			else if (comma_num == 1)
				pntr = &ar[2][0];
			comma_num++;
			continue ;
		}
		*pntr = rgb[i];
		pntr++;
	}
	return (color_code(ar));
}

/* A function thats being called by the one below it and its the
real function that check if the rgb as string is writen right */
int	rgb_check(char *rgb)
{
	int		i;
	int		j;
	int		comma_nbr;
	char	*nbr;

	i = -1;
	j = 0;
	comma_nbr = 0;
	if (rgb[0] != ' ')
		return (1);
	nbr = ft_calloc(1, ft_strlen(rgb));
	while (rgb[++i] && rgb[i] != '\n')
	{
		if (space_tabe(rgb[i]) && rgb[i +1] && ft_isdigit(rgb[i +1]) && nbr[0])
			return (1);
		if (rgb[i] == ' ' || rgb[i] == '\t')
			continue ;
		if (!ft_isdigit(rgb[i]) && !space_tabe(rgb[i]) && rgb[i] != ',')
			return (1);
		if (ft_isdigit(rgb[i]))
			nbr[j++] = rgb[i];
		if (comma_condition(&rgb[i], &j, &nbr[0], &comma_nbr))
			return (free(nbr), 1);
	}
	return (free(nbr), 0);
}

// Function that checks if the rgb lines are written in a good way
int	colors(char *line, int indx, int *result, t_game *game)
{
	if (line[indx] && line[indx] == 'F')
	{
		if (rgb_check(&line[indx + 1]))
			return (1);
		game->map.col[0] = read_rgb(&line[indx + 1]);
		result[4]++;
	}
	if (line[indx] && line[indx] == 'C')
	{
		if (rgb_check(&line[indx + 1]))
			return (1);
		game->map.col[1] = read_rgb(&line[indx + 1]);
		result[5]++;
	}
	return (0);
}
