/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_Main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:42:02 by azaghlou          #+#    #+#             */
/*   Updated: 2023/09/04 23:13:19 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// A function that check if the file path given exitst
int	check_file(char *file_name, int norm, mlx_texture_t **pntr)
{
	int	i;
	int	fd;

	i = 0;
	(void)norm;
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

/* Just a function that allocate a 2d array with a size of a string
and take a pointer to point to the first argument of that array  */
void	calloc_the_array(char ***ar, char *rgb, char **pntr)
{
	*ar = ft_calloc(sizeof(char *), 4);
	(*ar)[0] = ft_calloc(1, ft_strlen(rgb));
	(*ar)[1] = ft_calloc(1, ft_strlen(rgb));
	(*ar)[2] = ft_calloc(1, ft_strlen(rgb));
	(*ar)[3] = NULL;
	pntr[0] = &(*ar)[0][0];
}

// Function that checks if the textures lines are written in a good way
int	drction(char *line, int indx, int *result, t_game *game)
{
	if (exist_char(line, indx) && line[indx] == 'N' && line[indx + 1] == 'O')
	{
		if (check_file(&line[indx + 2], result[0]++, &game->map.tex[0]))
			return (0);
	}
	if (exist_char(line, indx) && line[indx] == 'S' && line[indx + 1] == 'O')
	{
		if (check_file(&line[indx + 2], result[1]++, &game->map.tex[1]))
			return (0);
	}
	if (exist_char(line, indx) && line[indx] == 'W' && line[indx + 1] == 'E')
	{
		if (check_file(&line[indx + 2], result[2]++, &game->map.tex[2]))
			return (0);
	}
	if (exist_char(line, indx) && line[indx] == 'E' && line[indx + 1] == 'A')
	{
		if (check_file(&line[indx + 2], result[3]++, &game->map.tex[3]))
			return (0);
	}
	return (1);
}

// The main file of checking the textures and the colors parsing part
int	clrs_and_textures_check(int fd, t_game *game)
{
	int		j;
	int		indx;
	char	*line;
	int		result[7];

	line = ft_strdup("");
	fill_int_arry_with_zero(result);
	while (line && !finished_that_check(result, line))
	{
		j = 0;
		indx = 0;
		result[6] = 0;
		free(line);
		line = get_next_line(fd);
		while (line && line[indx] && (line[indx] == ' ' || line[indx] == '\t'))
			indx++;
		if (drction(line, indx, result, game) && clrs(line, indx, result, game))
			return (free(line), 2);
	}
	if (!finished_that_check(result, line))
		return (free(line), 1);
	return (free(line), 0);
}

// The main file of all the parsing part
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
	rtrn += clrs_and_textures_check(fd, game);
	rtrn += map_check(fd, game);
	close(fd);
	return (rtrn);
}
