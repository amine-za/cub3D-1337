/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:45:58 by azaghlou          #+#    #+#             */
/*   Updated: 2023/09/05 00:50:27 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(mlx_image_t *img, t_vector2f p0, t_vector2f p1, int clr)
{
	t_vector3f	v;
	t_vector3f	d;
	int			i;

	v.x = p0.x;
	v.y = p0.y;
	d.x = p1.x - p0.x;
	d.y = p1.y - p0.y;
	d.z = d.y / d.x;
	if (fabs(d.x) >= fabs(d.y))
		d.z = fabs(d.x);
	else
		d.z = fabs(d.y);
	d.x = d.x / d.z;
	d.y = d.y / d.z;
	i = 1;
	while (i <= d.z)
	{
		if (v.x >= 0 && v.y >= 0 && v.x < img->width && v.y < img->height) 
			mlx_put_pixel(img, v.x, v.y, clr);
		v.x = v.x + d.x;
		v.y = v.y + d.y;
		i++;
	}
}

void	draw_cube(mlx_image_t *img, t_vector2i start, t_vector2i end, int color)
{
	t_vector2i	v;

	v.x = start.x;
	while (v.x <= end.x)
	{
		v.y = start.y;
		while (v.y <= end.y)
		{
			if (v.x >= 0 && v.y >= 0
				&& v.x < (int) img->width && v.y < (int) img->height) 
				mlx_put_pixel(img, v.x, v.y, color);
			v.y++;
		}
		v.x++;
	}
}

void	draw_circle(mlx_image_t *img, t_vector2i center, int r, int clr)
{
	int		x;
	int		y;
	float	deg;

	x = center.x;
	y = center.y;
	while (r)
	{
		deg = 0;
		while (deg < 360)
		{
			x = center.x + r * cos(deg * DR);
			y = center.y + r * sin(deg * DR);
			if (x >= 0 && y >= 0
				&& x < (int) img->width && y < (int) img->height) 
				mlx_put_pixel(img, x, y, clr);
			deg += 0.2;
		}
		r--;
	}
}

void	draw_rays(t_game *game, t_vector2f ray, int clr)
{
	int			s;
	t_vector2f	pp;
	t_vector2f	r;

	s = game->map.scale;
	r.x = ray.x / s;
	r.y = ray.y / s;
	pp.x = game->player.pos.x / s;
	pp.y = game->player.pos.y / s;
	if (r.x > 0 && r.y > 0 && r.x < WIDTH && r.y < HEIGHT)
		draw_line(game->map.img, pp, r, clr);
}

void	draw_map(t_game *game)
{
	t_vector2i	a;
	t_vector2i	b;
	t_vector2i	i;
	int			t;

	t = game->tile_size / game->map.scale;
	i.y = 0;
	while (i.y < game->map.size.y && game->map.map[i.y])
	{
		i.x = 0;
		while (i.x < game->map.size.x - 1 && game->map.map[i.y][i.x])
		{
			a.x = i.x * t;
			a.y = i.y * t;
			b.x = (i.x + 1) * t;
			b.y = (i.y + 1) * t;
			if (game->map.map[i.y][i.x] == '0')
				draw_cube(game->map.img, a, b, 0x8d99aeff);
			if (game->map.map[i.y][i.x] == '1')
				draw_cube(game->map.img, a, b, 0x2b2d42ff);
			i.x++;
		}
		i.y++;
	}
}
