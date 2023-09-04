/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:05:54 by yhachami          #+#    #+#             */
/*   Updated: 2023/09/04 17:41:10 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize(int width, int height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->width = width;
	game->height = height;
	mlx_delete_image(game->mlx, game->img);
	mlx_delete_image(game->mlx, game->map.img);
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	game->map.img = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		return ;
	if (!game->map.img
		|| mlx_image_to_window(game->mlx, game->map.img, 0, 0) < 0)
		return ;
}

void	draw_game(t_game *game)
{
	t_vector2i	a;
	t_vector2i	b;
	t_vector2i	p;

	a.x = 0;
	a.y = 0;
	b.x = game->width;
	b.y = game->height / 2;
	draw_cube(game->img, a, b, game->map.col[0]);
	a.x = 0;
	a.y = game->height / 2;
	b.x = game->width;
	b.y = game->height;
	draw_cube(game->img, a, b, game->map.col[1]);
	draw_map(game);
	draw_player(game);
	p.x = game->player.pos.x / game->map.scale;
	p.y = game->player.pos.y / game->map.scale;
	draw_circle(game->map.img, p, 2, 0x11FF00FF);
	draw_walls(game);
}

void	hookloop(void *param)
{
	t_game		*game;
	t_vector2f	pd;
	int			speed;

	game = (t_game *)param;
	draw_game(game);
	speed = 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.rot += 4;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.rot -= 4;
	pd.x = cos(game->player.rot * DR) * speed;
	pd.y = sin(game->player.rot * DR) * speed;
	move_up(game, pd);
	move_down(game, pd);
	move_right(game, pd);
	move_left(game, pd);
	game->player.rot = circle(game->player.rot);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		free_arr(game->map.map);
	}
}

void	init_game(t_game *game)
{
	game->fov = 100;
	game->column_size = 1;
	game->map.scale = 5;
	game->player.img_pos.x = 0; 
	game->player.img_pos.y = -50; 
	game->player.img_mult.x = 1;
	game->player.img_mult.y = -1;
	game->width = WIDTH;
	game->height = HEIGHT;
}

int	main(int ac, char **av)
{
	t_game	game;

	game.tile_size = 30;
	if (ac != 2 || parsing_main(&game, av[1]))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	init_game(&game);
	game.mlx = mlx_init(WIDTH, HEIGHT, "mossy rocks", true);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.map.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.player.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.player.tex = mlx_load_png("img/doom_shroom2.png");
	if (!game.img || mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
		return (0);
	if (!game.map.img || mlx_image_to_window(game.mlx, game.map.img, 0, 0) < 0)
		return (0);
	mlx_loop_hook(game.mlx, hookloop, &game);
	mlx_resize_hook(game.mlx, resize, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
}
