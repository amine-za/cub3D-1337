/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:42:42 by azaghlou          #+#    #+#             */
/*   Updated: 2023/08/23 13:17:58 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char **ar)
{
	int	i;

	i = -1;
	while (ar[++i])
		free(ar[i]);
	free(ar);
}

char	**arrjoin(char **ar, char *s, int size)
{
	char	**rtrn;
	int		i;
	int		j;

	i = -1;
	if (!s)
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
	rtrn[i] = ft_strdup(s);
	free_arr(ar);
	return (rtrn);
}

char	**map_to_ar(int fd)
{
	int		i;
	char	**map;
	char	*line;

	map = ft_calloc (sizeof(char *), 1);
	line = get_next_line(fd);
	while (1)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\n'))
			i++;
		if (line[i])
			break;
		free(line);
		line = get_next_line(fd);
	}
	map = arrjoin(map, line, i++);
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		map = arrjoin(map, line, i++);
	}
	free(line);
	return (map);
}

int	check_around_a_char(char **map, int j, int i, char c)
{
	if (map[j][i] == c)
	{
		if (i > ft_strlen(map[j - 1]) || map[j - 1][i] == ' ' || map[j - 1][i] == '\n')
			return (1);
		if (i > ft_strlen(map[j + 1]) || map[j + 1][i] == ' ' || map[j + 1][i] == '\n')
			return (1);
		if (i == 0 || map[j][i - 1] == ' ' || map[j][i - 1] == '\n')
			return (1);
		if (!map[j][i + 1] || map[j][i + 1] == ' ' || map[j][i + 1] == '\n')
			return (1);
	}
	return (0);
}

//i call this function to check the first and the last line
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

int map_check(int fd, t_game *game)
{
	int		i;
	int		j;
	int		x;
	char	**map;

	j = 0;
	x = 0;
	map = map_to_ar(fd);
	game->map.map = map;
	if (check_line(map[j]))
		return (free_arr(map), 1);
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			if (check_around_a_char(map, j, i, '0'))
				return (free_arr(map), 1);
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E' || map[j][i] == 'W')
			{
				if (check_around_a_char(map, j, i, map[j][i]))
					return (free_arr(map), 1);
				// printf("player (%d, %d)\n", i, j);
				game->player.pos.x = i * game->tile_size;
				game->player.pos.y = j * game->tile_size;
				game->player.rot = (float) rotation_of_player(map[j][i]);
				map[j][i] = '0';
				x++;
			}
			if (map[j][i] != '0' && map[j][i] != '1' && map[j][i] != ' ' &&
				map[j][i] != 'N' && map[j][i] != 'S' && map[j][i] != 'E' && map[j][i] != 'W')
				return (free_arr(map), 1);
			i++;
		}
		j++;
	}
	if (check_line(map[j - 1]))
		return (free_arr(map), 1);
	if (x != 1)
		return (free_arr(map), 1);
	game->map.size.y = j;
	game->map.size.x = tallest_line_length(map);
	return (0);
}
