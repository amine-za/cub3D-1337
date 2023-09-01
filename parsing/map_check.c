/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:42:42 by azaghlou          #+#    #+#             */
/*   Updated: 2023/09/01 19:06:45 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Function that take a file and returns it as a 2d array
char	**map_to_ar(int fd)
{
	int		i;
	char	**map;
	char	*line;

	map = ft_calloc(sizeof(char *), 1);
	line = get_next_line(fd);
	while (1)
	{
		i = 0;
		while (line[i] && (space_tabe(line[i]) || line[i] == '\n'))
			i++;
		if (line[i])
			break ;
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (NULL);
	}
	map = arrjoin(map, line, i++);
	while (line)
	{
		line = get_next_line(fd);
		map = arrjoin(map, &line[0], i++);
	}
	return (free(line), map);
}

// Function that checks that the character chould not be surrounded by any space
int	check_around_a_char(char **map, int j, int i, char c)
{
	if (map[j][i] == c)
	{
		if (i > ft_strlen(map[j - 1]) || map[j - 1][i] == ' ' || map[j
			- 1][i] == '\n')
			return (1);
		if (i > ft_strlen(map[j + 1]) || map[j + 1][i] == ' ' || map[j
			+ 1][i] == '\n')
			return (1);
		if (i == 0 || map[j][i - 1] == ' ' || map[j][i - 1] == '\n')
			return (1);
		if (!map[j][i + 1] || map[j][i + 1] == ' ' || map[j][i + 1] == '\n')
			return (1);
	}
	return (0);
}

// Return the angle of the player depand on the input
int	rotation_of_player(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (90);
	if (c == 'W')
		return (180);
	if (c == 'N')
		return (270);
	return (1);
}

/* Function loop on the map and check if a space character is in a good place 
          and not next to a '0' char or in the edge of the map,
                  and dealing with the rotation var.                        */
int	loop_on_map(char **map, t_game *game, int j, int *x)
{
	int	i;

	i = 0;
	while (map[j][i] && map[j][i] != '\n')
	{
		if (check_around_a_char(map, j, i, '0'))
			return (1);
		if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
			|| map[j][i] == 'W')
		{
			if (check_around_a_char(map, j, i, map[j][i]))
				return (1);
			game->player.pos.x = (i * game->tile_size) + 1;
			game->player.pos.y = (j * game->tile_size) + 1;
			game->player.rot = (float)rotation_of_player(map[j][i]);
			map[j][i] = '0';
			x[0]++;
		}
		if (map[j][i] != '0' && map[j][i] != '1' && map[j][i] != ' ' &&
			map[j][i] != 'N' && map[j][i] != 'S' && map[j][i] != 'E'
				&& map[j][i] != 'W')
			return (1);
		i++;
	}
	return (0);
}

// The main function of checking the map part of the file
int	map_check(int fd, t_game *game)
{
	int		x;
	int		j;
	char	**map;

	x = 0;
	j = -1;
	map = map_to_ar(fd);
	if (!map)
		return (1);
	game->map.map = map;
	if (check_line(map[++j]))
		return (free_arr(map), 1);
	while (map[++j])
	{
		if (loop_on_map(map, game, j, &x))
			return (free_arr(map), 1);
	}
	if (check_line(map[j - 1]))
		return (free_arr(map), 1);
	if (x != 1)
		return (free_arr(map), 1);
	game->map.size.y = j;
	game->map.size.x = tallest_line_length(map);
	return (0);
}
