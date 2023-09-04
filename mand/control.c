/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:52:00 by azaghlou          #+#    #+#             */
/*   Updated: 2023/09/01 20:55:46 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_game *game, t_vector2f pd)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player.pos.x += pd.x;
		game->player.pos.y += pd.y;
	}
}

void	move_down(t_game *game, t_vector2f pd)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player.pos.x -= pd.x;
		game->player.pos.y -= pd.y;
	}
}

void	move_right(t_game *game, t_vector2f pd)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.pos.x -= pd.y;
		game->player.pos.y += pd.x;
	}
}

void	move_left(t_game *game, t_vector2f pd)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player.pos.x += pd.y;
		game->player.pos.y -= pd.x;
	}
}
