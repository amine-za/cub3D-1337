/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_clrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:42:02 by azaghlou          #+#    #+#             */
/*   Updated: 2023/08/29 23:20:50 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_isdigit(int c)
{
        if (c <= '9' && c >= '0')
                return (1);
        return (0);
}

void	fill_int_arry_with_zero(int *result)
{
	result[0] = 0;
	result[1] = 0;
	result[2] = 0;
	result[3] = 0;
	result[4] = 0;
	result[5] = 0;
	result[6] = 0;
}

int	check_if_file_exist(char *file_name, int norm, mlx_texture_t **pntr)
{
	int	i;
	int fd;

	i = 0;
	(void) norm;
	//printf(" c = %c\n", file_name[0]);
	if (file_name[0] != ' ' && file_name[0] != '\t')
		return (0);
	while (file_name[i] && (file_name[i] == ' ' || file_name[i] == '\t'))
		i++;
	if (file_name[ft_strlen(file_name) - 1] == '\n')
		file_name[ft_strlen(file_name) - 1] = '\0';
	fd = open(&file_name[i], O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	*pntr = mlx_load_png(&file_name[i]);
	return (1);
}

int comma_condition(char *rgb, int *j, char *nbr, int *comma_nbr)
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

int rgb_check(char *rgb)
{
	int i;
	int j;
	int comma_nbr;
	char *nbr;

	i = -1;
	j = 0;
	comma_nbr = 0;
	if (rgb[0] != ' ')
		return (1);
	nbr = ft_calloc(1, ft_strlen(rgb));
	while (rgb[++i] && rgb[i] != '\n')
	{
		if ((rgb[i] == ' ' || rgb[i] == '\t') && rgb[i + 1] && ft_isdigit(rgb[i + 1]) && nbr[0]) 
			return (1);
		if (rgb[i] == ' ' || rgb[i] == '\t')
			continue;
		if (!ft_isdigit(rgb[i]) && rgb[i] != ' ' && rgb[i] != '\t' && rgb[i] != ',')
			return (1);
		if (ft_isdigit(rgb[i]))
			nbr[j++] = rgb[i];
		if (comma_condition(&rgb[i], &j, &nbr[0], &comma_nbr))
			return (free(nbr), 1);
	}
	return (free(nbr), 0);
}

unsigned int	color_code(char **ar)
{
	t_rgb	t;

	t.a = 255;
	t.r = ft_atoi(ar[0]);
	t.g = ft_atoi(ar[1]);
	t.b = ft_atoi(ar[2]);
	free_arr(ar);
	//printf(" ----------------------------\n");
	//printf("|  %d  |  %d  |  %d  |  %d  |\n", t.r, t.g, t.b, t.a);
	//printf(" ----------------------------\n");
	//printf("rgb2int = %u\n", rgb2int(t));
	return (rgb2int(t));
}

void	calloc_the_array(char ***ar, char *rgb)
{
	*ar = ft_calloc (sizeof(char *), 4);
	(*ar)[0] = ft_calloc(1, ft_strlen(rgb));
	(*ar)[1] = ft_calloc(1, ft_strlen(rgb));
	(*ar)[2] = ft_calloc(1, ft_strlen(rgb));
	(*ar)[3] = NULL;
}

unsigned int	read_rgb(char *rgb)
{
	int		i;
	char	*pntr;
	int		comma_num;
	char	**ar;

	i = 0;
	calloc_the_array(&ar, rgb);
	pntr = &ar[0][0];
	comma_num = 0;
	while (rgb[i] && rgb[i] != '\n')
	{
		while (rgb[i] == ' ' || rgb[i] == '\t')
			i++;
		if (rgb[i] == ',')
		{
			if (comma_num == 0)
				pntr = &ar[1][0];
			else if (comma_num == 1)
				pntr = &ar[2][0];
			comma_num++;
			i++;
			continue;
		}
		*pntr = rgb[i];
		pntr++;
		i++;
	}
	//printf("\n\n");
	//printf("		ar[0] = %s  ar[1] = %s  ar[2] = %s\n", ar[0], ar[1], ar[2]);
	return(color_code(ar));
}

int	finished_that_check(int *result)
{
	if (result[0] == 1 && result[1] == 1 && result[2] == 1 && result[3] == 1 && result[4] == 1 && result[5] == 1)
		return (1);
	return (0);
}

int	clrs_check(int fd, t_game *game)
{
	int		j;
	int		indx;
	char	*line;
	int		result[7];

	line = ft_strdup("");
	fill_int_arry_with_zero(result);
	while (line && !finished_that_check(result))
	{
		j = 0;
		indx = 0;
		result[6] = 0;
		free(line);
		line = get_next_line(fd);
		while (line[indx] && (line[indx] == ' ' || line[indx] == '\t'))
			indx++;
		if (ft_isdigit(line[indx]))
			break;
		if (line[indx] && line[indx + 1] && line[indx] == 'N' && line[indx + 1] == 'O')
		{
			if (!check_if_file_exist(&line[indx + 2], result[0]++, &game->map.tex[0]))
				return (1);
		}
		if (line[indx] && line[indx + 1] && line[indx] == 'S' && line[indx + 1] == 'O')
		{
			if (!check_if_file_exist(&line[indx + 2], result[1]++, &game->map.tex[1]))
				return (1);
		}
		if (line[indx] && line[indx + 1] && line[indx] == 'W' && line[indx + 1] == 'E')
		{
			if (!check_if_file_exist(&line[indx + 2], result[2]++, &game->map.tex[2]))
				return (1);
		}
		if (line[indx] && line[indx + 1] && line[indx] == 'E' && line[indx + 1] == 'A')
		{
			if (!check_if_file_exist(&line[indx + 2], result[3]++, &game->map.tex[3]))
				return (1);
		}
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
	}
	free(line);
	if (!finished_that_check(result))
		return (1);
	return (0);
}

int	parsing_main(t_game *game, char *map)
{
	int	fd;
	int	rtrn;

	rtrn = 0;	
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (1);
	if (ft_strncmp(&map[ft_strlen(map) - 4], ".cub", ft_strlen(map)))
		return (1);
	// rtrn += clrs_check(fd);
	// rtrn += map_check(fd);
	printf("colors check--> %d\n", rtrn += clrs_check(fd, game));
	printf("map check   --> %d\n\n", rtrn += map_check(fd, game));
	close (fd);
	return (rtrn);
}
