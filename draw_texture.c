/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:28:17 by yhachami          #+#    #+#             */
/*   Updated: 2023/09/04 17:36:31 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_to_image(t_game *game, t_vector2i img_pos, float sx, float sy)
{
	mlx_texture_t	*tex;
	uint8_t			*pxx;
	uint8_t			*pxi;
	int				i;
	int				j;

	tex = game->player.tex;
	j = -1;
	while (++j * sx < tex->width)
	{
		i = -1;
		while (++i * sy < tex->height)
		{
			if ((i + img_pos.y) < game->player.img->height
				&& (j + img_pos.x) < game->player.img->width)
			{
				pxx = &tex->pixels[(((int)(i * sy) *tex->width) 
						+ (int)(j * sx)) * tex->bytes_per_pixel];
				pxi = &game->player.img->pixels[((i + img_pos.y) 
						* game->player.img->width + (j + img_pos.x))
					* tex->bytes_per_pixel];
				ft_memmove(pxi, pxx, tex->bytes_per_pixel);
			}
		}
	}
}

void	draw_player(t_game *game)
{
	t_vector2i	img_pos;
	float		s;

	mlx_delete_image(game->mlx, game->player.img);
	game->player.img = mlx_new_image(game->mlx, game->width, game->height);
	s = scale(game);
	game->player.img_pos.x += 1 * game->player.img_mult.x;
	img_pos.x = (game->width / 2) - game->player.img_pos.x;
	if (game->player.img_pos.x > 70)
		game->player.img_mult.x = -1;
	if (game->player.img_pos.x < -70)
		game->player.img_mult.x = 1;
	game->player.img_pos.y += 1 * game->player.img_mult.y;
	img_pos.y = game->height - (game->player.tex->height / s)
		- game->player.img_pos.y;
	if (game->player.img_pos.y > -1)
		game->player.img_mult.y = -1;
	if (game->player.img_pos.y < -120)
		game->player.img_mult.y = 1;
	player_to_image(game, img_pos, s, s);
	if (!game->player.img
		|| mlx_image_to_window(game->mlx, game->player.img, 0, 0) < 0)
		return ;
}

void	texture_to_image(t_game *game, t_ray ray, t_vector2i a, t_vector2f wall)
{
	mlx_texture_t	*tex;
	uint8_t			*pixelx;
	uint8_t			*pixeli;
	t_vector2f		r;
	int				i;

	tex = game->tex;
	wall.y = 1;
	if (ray.wall_height > game->height)
		wall.y = ((game->height - ray.wall_height) / 2);
	r.x = (float) wall.x * (tex->width / game->tile_size);
	i = 0;
	while (i < ray.wall_height && i < game->height)
	{
		r.y = (float)(i - wall.y) *(tex->height / ray.wall_height);
		if ((((int) r.y * tex->width) + (int) r.x) < (tex->width * tex->height))
		{
			pixelx = &tex->pixels[((((int) r.y) * tex->width)
					+ ((int) r.x)) * tex->bytes_per_pixel];
			pixeli = &game->img->pixels[((a.y + i)
					* game->img->width + (a.x)) * tex->bytes_per_pixel];
			ft_memmove(pixeli, pixelx, tex->bytes_per_pixel);
		}
		i++;
	}
}

void	draw_texture(t_game *game, t_ray ray, t_vector2i a)
{
	t_vector2f	wall;

	if (ray.pos_in_tile.y == 0)
	{
		game->tex = game->map.tex[0];
		wall.x = ray.pos_in_tile.x;
	}
	if (ray.pos_in_tile.y >= game->tile_size - 0.01)
	{
		game->tex = game->map.tex[1];
		wall.x = ray.pos_in_tile.x;
	}
	if (ray.pos_in_tile.x == 0)
	{
		game->tex = game->map.tex[2];
		wall.x = ray.pos_in_tile.y;
	}
	if (ray.pos_in_tile.x >= game->tile_size - 0.01)
	{
		game->tex = game->map.tex[3];
		wall.x = ray.pos_in_tile.y;
	}
	texture_to_image(game, ray, a, wall);
}

void	draw_colum(t_game *game, int x, t_ray ray)
{
	t_vector2i	a;
	t_vector2i	b;
	int			c;
	int			h;

	c = game->column_size;
	ray.wall_height = (game->tile_size * game->height) / ray.dst;
	h = ray.wall_height;
	if (h > game->height)
		h = game->height;
	a.x = x;
	a.y = (game->height / 2) - (h / 2);
	b.x = x + c;
	b.y = (game->height / 2) + (h / 2);
	if (a.y < 1)
		a.y = 1;
	if (b.y > game->height - 1)
		b.y = game->height - 1;
	if (a.x >= 0 && a.x < game->width && a.y >= 0 && a.y < game->height
		&& b.x >= 0 && b.x < game->width && b.y >= 0 && b.y < game->height)
	{
		draw_texture(game, ray, a);
	}
}
