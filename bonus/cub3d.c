/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:05:54 by yhachami          #+#    #+#             */
/*   Updated: 2023/09/01 23:38:00 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game)
{
	t_vector2i	img_pos;

	mlx_delete_image(game->mlx, game->player.img);
	game->player.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->player.img_pos.x += 1.2 * game->player.img_mult.x;
	img_pos.x = (WIDTH / 2) - game->player.img_pos.x;
	if (game->player.img_pos.x > 70)
		game->player.img_mult.x = -1;
	if (game->player.img_pos.x < -70)
		game->player.img_mult.x = 1;
	game->player.img_pos.y += 1 * game->player.img_mult.y;
	img_pos.y = HEIGHT - (game->player.tex->height / 2)
		- game->player.img_pos.y;
	if (game->player.img_pos.y > -1)
		game->player.img_mult.y = -1;
	if (game->player.img_pos.y < -120)
		game->player.img_mult.y = 1;
	player_to_image(game, img_pos, 2, 2);
	if (mlx_image_to_window(game->mlx, game->player.img, 0, 0) < 0)
		return ;
}

void	draw_game(t_game *game)
{
	t_vector2i	a;
	t_vector2i	b;
	t_vector2i	p;	

	a.x = 0;
	a.y = 0;
	b.x = WIDTH;
	b.y = HEIGHT / 2;
	draw_cube(game->img, a, b, game->map.col[0]);
	a.x = 0;
	a.y = HEIGHT / 2;
	b.x = WIDTH;
	b.y = HEIGHT;
	draw_cube(game->img, a, b, game->map.col[1]);
	draw_map(game);
	draw_player(game);
	p.x = game->player.pos.x / game->map.scale;
	p.y = game->player.pos.y / game->map.scale;
	draw_circle(game, p, 2, 0x11FF00FF);
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
	game->fov = 70;
	game->column_size = 1;
	game->map.scale = 5;
	game->player.img_pos.x = 0; 
	game->player.img_pos.y = -50; 
	game->player.img_mult.x = 1;
	game->player.img_mult.y = -1;
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
	if (!game.img || mlx_image_to_window(game.mlx, game.map.img, 0, 0) < 0)
		return (0);
	mlx_loop_hook(game.mlx, hookloop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
}
