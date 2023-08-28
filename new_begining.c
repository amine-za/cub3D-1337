/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_begining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:52:00 by azaghlou          #+#    #+#             */
/*   Updated: 2023/08/28 16:40:56 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	draw_55ttt(t_game *game, t_vector2f start, t_vector2f end, int clr)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	step;
	int		i;

	x = start.x;
	y = start.y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dy = dy / step;
	dx = dx / step;
	i = 0;
	while (i <= step)
	{
		if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
			mlx_put_pixel(game->map.img,(int) x,(int) y, clr);
		x += dx;
		y += dy;
		i++;
	}
}

void	draw_55t(t_game *game, t_vector2f start, t_vector2f end, int clr)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	step;
	int		i;

	x = start.x;
	y = start.y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dy = dy / step;
	dx = dx / step;
	i = 0;
	while (i <= step)
	{
		if (y / game->tile_size < game->map.size.y && x / game->tile_size >= 0 && y / game->tile_size >= 0 
			&& x / game->tile_size <= ft_strlen(game->map.map[(int) y / game->tile_size])
				&& game->map.map[(int )y / game->tile_size][(int) x / game->tile_size] == '1')
		{
			
			break;
		}
		if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
			mlx_put_pixel(game->map.img,(int) x,(int) y, clr);
		x += dx;
		y += dy;
		i++;
	}
}

void	draw_morabe3(t_game *game, t_vector2i start, t_vector2i end, int clr)
{
	int i;
	int	j;

	i = start.x;
	while (i <= end.x)
	{
		j = start.y;
		while (j <= end.y)
		{
			mlx_put_pixel(game->map.img, i, j, clr);
			j++;
		}
		i++;
	}
}

void	draw_dowara(t_game *game, t_vector2i center, int r, int clr)
{
	int x;
	int	y;
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
			mlx_put_pixel(game->map.img, x, y, clr);
			deg += 0.2;
		}
		r--;
	}
}

void	draw_map(t_game *game)
{
	t_vector2i	indx;
	t_vector2i	start;
	t_vector2i	end;
	t_vector2i	p;
	int	tile;

	tile = game->tile_size;
	start.y = 2;
	end.y = tile;
	indx.y = 0;
	while (game->map.map[indx.y])
	{
		indx.x = 0;
		start.x = 2;
		end.x = tile;
		while (game->map.map[indx.y][indx.x])
		{
			if (game->map.map[indx.y][indx.x] == '1')
				draw_morabe3(game, start, end, 0xE86A33ff);
			if (game->map.map[indx.y][indx.x] == '0')
				draw_morabe3(game, start, end, 0xF2E3DBff);
			if (game->map.map[indx.y][indx.x] == ' ')
				draw_morabe3(game, start, end, 0x263A29ff);
			indx.x++;
			start.x += tile;
			end.x += tile;
		}
		indx.y++;
		start.y += tile;
		end.y += tile;
	}
	// mlx_put_pixel(game->map.img, game->player.pos.x, game->player.pos.y, 0xFF0000FF);
	p.x = game->player.pos.x;
	p.y = game->player.pos.y;
	draw_dowara(game, p, 3, 0xFF0000FF);
}

void	hooploop(void *param)
{
	t_game *game;
	float	dcos;
	float	dsin;
	int		speed;
	t_vector2f player_pos;
	t_vector2f player_dir;

	speed = 2;
	game = (t_game *)param;
	mlx_delete_image(game->mlx, game->map.img);
	game->map.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);

	draw_map(game);
	// rycasting(game);
	
	float rot = game->player.rot -30;
	int i = 0;
	while (i < 60)
	{
		// direction
		dcos = cos(rot * DR) * speed;
		dsin = sin(rot * DR) * speed;

		//player direction ray
		player_pos.x = game->player.pos.x;
		player_pos.y = game->player.pos.y;
		player_dir.x = game->player.pos.x + dcos * 1000;
		player_dir.y = game->player.pos.y + dsin * 1000;
		draw_55t(game, player_pos, player_dir, 0xff00ffff);
		rot++;
		i++;
	}
	// movement
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player.pos.x += dcos;
		game->player.pos.y += dsin;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player.pos.x -= dcos;
		game->player.pos.y -= dsin;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.pos.x -= dsin;
		game->player.pos.y += dcos;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player.pos.x += dsin;
		game->player.pos.y -= dcos;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.rot++;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.rot--;
	printf("%f\n", game->player.rot);
	if (game->player.rot > 360)
		game->player.rot -= 360;
	if (game->player.rot < 0)
		game->player.rot += 360;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);

	if (mlx_image_to_window(game->mlx, game->map.img, 0, 0) < 0)
		mlx_close_window(game->mlx);
}
