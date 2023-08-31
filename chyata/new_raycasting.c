/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:54:31 by azaghlou          #+#    #+#             */
/*   Updated: 2023/08/31 05:22:05 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ray_check(t_ray *ray, t_game *game)
{
	while (ray->dof)
	{
		ray->tile.y = (int)(ray->ray.y / game->tile_size);
		ray->tile.x = (int)(ray->ray.x / game->tile_size);
		if (ray->tile.y < game->map.size.y && ray->tile.x >= 0 && ray->tile.y >= 0 
			&& ray->tile.x <= ft_strlen(game->map.map[ray->tile.y]) 
			&& game->map.map[ray->tile.y][ray->tile.x] == '1')
			break;
		ray->ray.x += ray->step.x;
		ray->ray.y += ray->step.y;
		ray->dof--;
	}
}

t_vector2f	in_vertical_tiles(t_ray *ray, t_game *game, float alpha_ray)
{
	t_vector2f	p;
	
	p = game->player.pos;
	ray->ray.y = game->player.pos.y;
	ray->ray.x = game->player.pos.x;
	ray->dof = 50;
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
		ray->dof = 0;
	ray_check(ray, game);
	return (ray->ray);
}

t_vector2f	in_horizontal_tiles(t_ray *ray, t_game *game, float alpha_ray)
{
	t_vector2f p;

	p = game->player.pos;
	ray->ray.y = game->player.pos.y;
	ray->ray.x = game->player.pos.x;
	ray->dof = 50;
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
		ray->dof = 0;
	ray_check(ray, game);
	return (ray->ray);
}

t_ray	distance2(t_game *game, t_vector2f hray, t_vector2f vray, t_ray *ray)
{
	t_vector2f	d;
	float		fish;

	fish = game->player.rot - ray->angel;
	d.x = pythagoras(hray.x - game->player.pos.x, hray.y - game->player.pos.y);	
	d.y = pythagoras(vray.x - game->player.pos.x, vray.y - game->player.pos.y);
	if (d.x > d.y)
	{
		ray->dst = d.y;
		ray->ray = vray;
	}
	else
	{
		ray->dst = d.x;
		ray->ray = hray;
	}
	ray->tile.x = ray->ray.x / game->tile_size;
	ray->tile.y = ray->ray.y / game->tile_size;
	ray->pos_in_tile.x = ray->ray.x - (ray->tile.x * game->tile_size);
	ray->pos_in_tile.y = ray->ray.y - (ray->tile.y * game->tile_size);
	ray->dst = ray->dst * cos(fish * DR);
	draw_rays(game, ray->ray);
	return (*ray);
}

void	rycasting(t_game *game)
{
	t_ray		ray;
	t_vector2f	vertical_ray;
	t_vector2f	horizontal_ray;
	int			x;

	x = 0;
	ray.angel_step = (float) game->fov / (WIDTH / game->column_size);
	ray.angel = circle(game->player.rot - (float) game->fov / 2);
	while(x != WIDTH / game->column_size)
	{
		vertical_ray = in_vertical_tiles(&ray, game, ray.angel);
		horizontal_ray = in_horizontal_tiles(&ray, game, ray.angel);
		distance2(game, horizontal_ray, vertical_ray, &ray);
		draw_colum(game, x * game->column_size, ray);	
		ray.angel = circle(ray.angel + ray.angel_step);
		x++;
	}
}
