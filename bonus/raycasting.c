/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:02:02 by yhachami          #+#    #+#             */
/*   Updated: 2023/09/05 20:08:37 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizon_ray(t_game *game, t_ray *ray)
{
	t_vector2f	p;
	int			ts;

	p = game->player.pos;
	ts = game->tile_size;
	ray->ray.x = game->player.pos.x;
	ray->ray.y = game->player.pos.y;
	ray->dof = game->map.size.x * game->map.size.y;
	if (ray->angel > 180)
	{
		ray->ray.y = (((int) p.y / ts) * ts) - 0.001;
		ray->ray.x = -(p.y - ray->ray.y) / tan(ray->angel * DR) + p.x;
		ray->step.y = -ts;
		ray->step.x = -ts / tan(ray->angel * DR);
	}
	else if (ray->angel < 180)
	{
		ray->ray.y = ((int) p.y / ts) * ts + ts;
		ray->ray.x = -(p.y - ray->ray.y) / tan(ray->angel * DR) + p.x;
		ray->step.y = ts;
		ray->step.x = ts / tan(ray->angel * DR);
	}
	else 
		ray->dof = 0;
}

void	vertical_ray(t_game *game, t_ray *ray)
{
	t_vector2f	p;
	int			ts;

	p = game->player.pos;
	ts = game->tile_size;
	ray->ray.x = game->player.pos.x;
	ray->ray.y = game->player.pos.y;
	ray->dof = game->map.size.x * game->map.size.y;
	if (ray->angel > 90 && ray->angel < 270)
	{
		ray->ray.x = (((int) p.x / ts) * ts) - 0.001;
		ray->ray.y = -(p.x - ray->ray.x) * tan(ray->angel * DR) + p.y;
		ray->step.x = -ts;
		ray->step.y = -ts * tan(ray->angel * DR);
	}
	else if (ray->angel < 90 || ray->angel > 270)
	{
		ray->ray.x = ((int) p.x / ts) * ts + ts;
		ray->ray.y = -(p.x - ray->ray.x) * tan(ray->angel * DR) + p.y;
		ray->step.x = ts;
		ray->step.y = ts * tan(ray->angel * DR);
	}
	else 
		ray->dof = 0;
}

t_vector2f	cast_rays(t_game *game, t_ray *ray)
{
	t_vector2f	outray;

	outray.x = (game->map.size.x * game->map.size.y) * 10;
	outray.y = (game->map.size.x * game->map.size.y) * 10;
	while (ray->dof > 0)
	{
		ray->tile.x = (int) ray->ray.x / game->tile_size;
		ray->tile.y = (int) ray->ray.y / game->tile_size;
		if (ray->tile.x >= 0 && ray->tile.y >= 0 
			&& ray->tile.y < game->map.size.y
			&& ray->tile.x <= ft_strlen(game->map.map[ray->tile.y])
			&& game->map.map[ray->tile.y][ray->tile.x] == '1')
		{
			outray = ray->ray;
			break ;
		}
		else
		{
			ray->ray.x += ray->step.x;
			ray->ray.y += ray->step.y;
			ray->dof--;
		}
	}
	return (outray);
}

int	distance(t_game *game, t_vector2f hray, t_vector2f vray, t_ray *ray)
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
	draw_rays(game, ray->ray, 0xaa1a00ff);
	return (ray->dst);
}

void	draw_walls(t_game *game)
{
	t_ray		ray;
	t_vector2f	vray;
	t_vector2f	hray;
	int			x;

	x = 0;
	ray.angel_step = (float) game->fov / (WIDTH / game->column_size);
	ray.angel = circle(game->player.rot - (float) game->fov / 2);
	while (x < WIDTH - 1)
	{
		horizon_ray(game, &ray);
		hray = cast_rays(game, &ray);
		vertical_ray(game, &ray);
		vray = cast_rays(game, &ray);
		distance(game, hray, vray, &ray);
		draw_colum(game, x, ray);
		ray.angel = circle(ray.angel + ray.angel_step);
		x += game->column_size;
	}
}
