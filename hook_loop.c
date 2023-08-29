/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:52:00 by azaghlou          #+#    #+#             */
/*   Updated: 2023/08/29 21:11:16 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	move_up(t_game *game, t_vector2f pd)
{
	t_vector2i	ptile;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		ptile.x = (int) (game->player.pos.x + pd.x * 5) / game->tile_size;
		ptile.y = (int) (game->player.pos.y + pd.y * 5) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 && ptile.x < game->map.size.x && ptile.y < game->map.size.y
				&& game->map.map[ptile.y][ptile.x] != '1')
		{
			game->player.pos.x += pd.x;
			game->player.pos.y += pd.y;
		}
	}
}
void	move_down(t_game *game, t_vector2f pd)
{
	t_vector2i	ptile;

	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		ptile.x = (int) (game->player.pos.x - pd.x * 5) / game->tile_size;
		ptile.y = (int) (game->player.pos.y - pd.y * 5) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 && ptile.x < game->map.size.x && ptile.y < game->map.size.y
				&& game->map.map[ptile.y][ptile.x] != '1')
		{
			game->player.pos.x -= pd.x;
			game->player.pos.y -= pd.y;
		}
	}
}

void	move_right(t_game *game, t_vector2f pd)
{
	t_vector2i	ptile;

	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		ptile.x = (int) (game->player.pos.x - pd.x * 5) / game->tile_size;
		ptile.y = (int) (game->player.pos.y + pd.y * 5) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 && ptile.x < game->map.size.x && ptile.y < game->map.size.y
				&& game->map.map[ptile.y][ptile.x] != '1')
		{
			game->player.pos.x -= pd.y;
			game->player.pos.y += pd.x;
		}
	}
}
void	move_left(t_game *game, t_vector2f pd)
{
	t_vector2i	ptile;

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		ptile.x = (int) (game->player.pos.x + pd.y * 5) / game->tile_size;
		ptile.y = (int) (game->player.pos.y - pd.x * 5) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 && ptile.x < game->map.size.x && ptile.y < game->map.size.y
				&& game->map.map[ptile.y][ptile.x] != '1')
		{
			game->player.pos.x += pd.y;
			game->player.pos.y -= pd.x;
		}
	}
}

void	hookloop(void *param)
{
	t_game  	*game;
	t_vector2f	pd;
	int			speed;

	game = (t_game *)param;
	draw_game(game);
	speed = 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.rot += 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.rot -= 2;
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
		//free(game->p);
	}
}

