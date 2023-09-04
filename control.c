/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:52:00 by azaghlou          #+#    #+#             */
/*   Updated: 2023/09/04 17:02:24 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_game *game, t_vector2f pd)
{
	t_vector2i	ptile;
	t_vector2f	p;

	p = game->player.pos;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		ptile.x = (int)(p.x + pd.x * 2) / game->tile_size;
		ptile.y = (int)(p.y + pd.y * 2) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 
			&& ptile.x < game->map.size.x && ptile.y < game->map.size.y
			&& game->map.map[ptile.y][ptile.x] != '1'
			&& game->map.map[(int) p.y / game->tile_size][ptile.x] != '1'
			&& game->map.map[ptile.y][(int) p.x / game->tile_size] != '1')
		{
			game->player.pos.x += pd.x;
			game->player.pos.y += pd.y;
		}
	}
}

void	move_down(t_game *game, t_vector2f pd)
{
	t_vector2i	ptile;
	t_vector2f	p;

	p = game->player.pos;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		ptile.x = (int)(p.x - pd.x * 2) / game->tile_size;
		ptile.y = (int)(p.y - pd.y * 2) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 
			&& ptile.x < game->map.size.x && ptile.y < game->map.size.y
			&& game->map.map[ptile.y][ptile.x] != '1'
			&& game->map.map[(int) p.y / game->tile_size][ptile.x] != '1'
			&& game->map.map[ptile.y][(int) p.x / game->tile_size] != '1')
		{
			game->player.pos.x -= pd.x;
			game->player.pos.y -= pd.y;
		}
	}
}

void	move_right(t_game *game, t_vector2f pd)
{
	t_vector2i	ptile;
	t_vector2f	p;

	p = game->player.pos;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		ptile.x = (int)(p.x - pd.y * 2) / game->tile_size;
		ptile.y = (int)(p.y + pd.x * 2) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 
			&& ptile.x < game->map.size.x && ptile.y < game->map.size.y
			&& game->map.map[ptile.y][ptile.x] != '1'
			&& game->map.map[(int) p.y / game->tile_size][ptile.x] != '1'
			&& game->map.map[ptile.y][(int) p.x / game->tile_size] != '1')
		{
			game->player.pos.x -= pd.y;
			game->player.pos.y += pd.x;
		}
	}
}

void	move_left(t_game *game, t_vector2f pd)
{
	t_vector2i	ptile;
	t_vector2f	p;

	p = game->player.pos;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		ptile.x = (int)(p.x + pd.y * 2) / game->tile_size;
		ptile.y = (int)(p.y - pd.x * 2) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 
			&& ptile.x < game->map.size.x && ptile.y < game->map.size.y
			&& game->map.map[ptile.y][ptile.x] != '1'
			&& game->map.map[(int) p.y / game->tile_size][ptile.x] != '1'
			&& game->map.map[ptile.y][(int) p.x / game->tile_size] != '1')
		{
			game->player.pos.x += pd.y;
			game->player.pos.y -= pd.x;
		}
	}
}
