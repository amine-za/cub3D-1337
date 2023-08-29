/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:54:31 by azaghlou          #+#    #+#             */
/*   Updated: 2023/08/29 21:05:50 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	pythagoras_fct(float a, float b)
{
	return (sqrt((a * a) + (b * b)));
}

void	ray_check(int count, t_ray *ray, t_game *game)
{
	while (count)
	{
		ray->tile.y = (int)(ray->ray.y / game->tile_size);
		ray->tile.x = (int)(ray->ray.x / game->tile_size);
		// printf("V o %d  k %d\n", ray->tile.y, ray->tile.x);
		if (ray->tile.y < game->map.size.y && ray->tile.x >= 0 && ray->tile.y >= 0 
			&& ray->tile.x <= ft_strlen(game->map.map[ray->tile.y]) && game->map.map[ray->tile.y][ray->tile.x] == '1')
			break;
		ray->ray.x += ray->step.x;
		ray->ray.y += ray->step.y;
		count--;
	}
}

t_vector2f	in_vertical_tiles(t_ray *ray, t_game *game, float alpha_ray)
{
	t_vector2f	p;
	
	ray->ray.y = 0;
	ray->ray.x = 0;
	ray->count = 10;
	p = game->player.pos;
	if (alpha_ray < 90 || alpha_ray > 270)
	{
		ray->ray.x = (((int)p.x / game->tile_size) * game->tile_size) + game->tile_size;
		ray->ray.y = p.y + ((ray->ray.x - p.x) * tan(alpha_ray * DR));
		ray->step.x = game->tile_size;
		ray->step.y = game->tile_size * tan(alpha_ray * DR);
	}
	else if (alpha_ray > 90 && alpha_ray < 270)
	{
		ray->ray.x = (((int)p.x / game->tile_size) * game->tile_size) - 1;
		ray->ray.y = p.y + ((ray->ray.x - p.x) * tan(alpha_ray * DR));
		ray->step.x = -game->tile_size;
		ray->step.y = -(game->tile_size * tan(alpha_ray * DR));
	}
	else
		ray->count = 0;
	ray_check(ray->count, ray, game);
	return (ray->ray);
}

t_vector2f	in_horizontal_tiles(t_ray *ray, t_game *game, float alpha_ray)
{
	t_vector2f p;

	ray->ray.y = 0;
	ray->ray.x = 0;
	ray->count = 10;
	p = game->player.pos;
	if (alpha_ray > 0 && alpha_ray < 180)
	{
		ray->ray.y = (((int)p.y / game->tile_size) * game->tile_size) + game->tile_size;
		ray->ray.x = p.x + ((ray->ray.y - p.y) / tan(alpha_ray * DR));
		ray->step.y = game->tile_size;
		ray->step.x = game->tile_size / tan(alpha_ray * DR);
	}
	else if (alpha_ray > 180)
	{
		ray->ray.y = (((int)p.y / game->tile_size) * game->tile_size) - 1;
		ray->ray.x = p.x + ((ray->ray.y - p.y) / tan(alpha_ray * DR));
		ray->step.y = -game->tile_size;
		ray->step.x = -(game->tile_size / tan(alpha_ray * DR));
	}
	else
		ray->count = 0;
	ray_check(ray->count, ray, game);
	return (ray->ray);
}

void	draw_7iit(int x, float ray_lenght, t_game *game)
{
	int			column;
	t_vector2i	start;
	t_vector2i	end;
	int			h;

	column = WIDTH / 60;
	start.x = x * column;
	// printf("h %f\n", ray_lenght);
	h = (HEIGHT * 20) / ray_lenght;
	start.y = (HEIGHT/2) - h;
	// start.y = x * column;
	end.x = start.x + column;
	end.y = (HEIGHT/2) + h;
	if (start.y < 0)
		start.y = 0;
	if (end.y > HEIGHT)
		end.y = HEIGHT;
	draw_cube(game->img, start, end, 0x777777ff);
}

void	rycasting(t_game *game)
{
	t_ray ray;
	int			x;
	t_vector2f vertical_ray;
	t_vector2f horizontal_ray;
	t_vector2f p;
	float 	vertical_distance;
	float 	horizontal_distance;
	float 	distance;
	float	alpha_ray;

	x = 0;
	p = game->player.pos;
	alpha_ray = game->player.rot - 30;
	while(x != 60)
	{
		// vertical ray
		vertical_ray = in_vertical_tiles(&ray, game, alpha_ray);
		vertical_distance = pythagoras_fct(ray.ray.x - p.x, ray.ray.y - p.y);
		// horizontal ray
		horizontal_ray = in_horizontal_tiles(&ray, game, alpha_ray);
		horizontal_distance = pythagoras_fct(ray.ray.x - p.x, ray.ray.y - p.y);
	
		if (vertical_distance > horizontal_distance)
			draw_line(game->img, p, horizontal_ray, 0x11AA00ff);
		else
			draw_line(game->img, p, vertical_ray, 0xAA0000ff);
		
		if (vertical_distance > horizontal_distance)
			distance = horizontal_distance;
		else
			distance = vertical_distance;

		draw_7iit(x, distance, game);
		alpha_ray++;
		x++;
		if (alpha_ray >= 360)
			alpha_ray = 0;
	}
}
