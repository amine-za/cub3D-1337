/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:05:54 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/29 21:15:32 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

float	dst(t_vector2f a, t_vector2f b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

float	circle(float fish)
{
	if (fish >= 360)
		fish -= 360;
	if (fish < 0)
		fish += 360;
	return (fish);
}


void draw_texture(t_game *game, uint32_t h2, t_vector2i a, t_ray ray)
{
	mlx_texture_t*	tex;
	uint8_t*		pixelx;
	uint8_t*		pixeli;
	uint32_t		i;
	uint32_t		j;
	uint32_t		z;
	float			r;
	float			r2;
	float			rx;
	float			ry;
	int				h;
	int				px;
	int				py;
	int				x;
	int				y;

	//h = (ray.dst / 2) + 200;
	//h = ray.dst;
	h = (game->tile_size * HEIGHT) / ray.dst;
	px = ray.ray.x - (ray.tile.x * game->tile_size);
	py = ray.ray.y - (ray.tile.y * game->tile_size);
	if (py == 0)
	{
		tex = game->map.tex[1];
		x = px;
	}
	else if (py == 49)
	{
		tex = game->map.tex[0];
		x = px;
	}
	else if (px == 0)
	{
		tex = game->map.tex[3];
		x = py;
	}
	else if (px == 49)
	{
		tex = game->map.tex[2];
		x = py;
	}
	y = 0;
	if (h > HEIGHT)
		y = (HEIGHT - h) / 2;

	r = (float) tex->height / h;
	r2 = (float) tex->width / game->tile_size;
	//printf("r = %f, r2 = %f, h = %d\n", r, r2, h);

	j = 0;
	// while (j < game->column_size)
	// {
		rx = (float) x * r2;
		i = 0;
		z = 0;
		while (i < h2)
		{
			ry = (float) (z - y) * r;
			if (ry > tex->height)
				ry = (float) z * r;
			pixelx = &tex->pixels[((((int) ry) * tex->width) + ((int) rx)) * tex->bytes_per_pixel];
			pixeli = &game->img->pixels[((a.y + i) * game->img->width + (a.x + j)) * tex->bytes_per_pixel];
			ft_memmove(pixeli, pixelx, tex->bytes_per_pixel);
			i++;
			z++;
			if (ry > tex->height)
				z = 0;
		}
		// j++;
	// }
}

void	draw_game(t_game *game)
{
	t_vector2i	a;
	t_vector2i	b;

	// sky
	a.x = 0;
	a.y = 0;
	b.x = WIDTH;
	b.y = HEIGHT / 2;
	draw_cube(game->img, a, b, game->map.col[0]);
	// floor
	a.x = 0;
	a.y = HEIGHT / 2;
	b.x = WIDTH;
	b.y = HEIGHT;
	draw_cube(game->img, a, b, game->map.col[1]);
	// map
	draw_map(game);
	// player
	a.x = game->player.pos.x / game->map.scale;
	a.y = game->player.pos.y / game->map.scale;
	draw_circle(game, a, 2, 0x11FF00FF);
	// walls
	// rycasting(game);
	draw_walls(game);
}


int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
	{
		game.tile_size = 32;
		if (parsing_main(&game, av[1]))
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		game.fov = 60;
		// game->column_size = WIDTH / game->fov;
		game.column_size = 1;
		game.map.scale = 5;
		// printf("player (%f, %f)\n", game.player.pos.x, game.player.pos.y);
		// printf("size (%d, %d)\n", game.map.size.x, game.map.size.y);
		game.mlx = mlx_init(WIDTH, HEIGHT, "mossy rocks", true);
		game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		game.map.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		game.map.img = mlx_new_image(game.mlx, (game.map.size.x + 1) * game.tile_size, (game.map.size.y + 1) * game.tile_size);
		if (!game.img || mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
			return (0);
		if (!game.img || mlx_image_to_window(game.mlx, game.map.img, 0, 0) < 0)
			return (0);
		mlx_loop_hook(game.mlx, hookloop, &game);
		// mlx_key_hook(game.mlx, &movehook, &game);
		mlx_loop(game.mlx);
		mlx_terminate(game.mlx);
	}
}
