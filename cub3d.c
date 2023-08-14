/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:05:54 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/14 12:25:10 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

float	dst(t_vector2f a, t_vector2f b)
{
	// ok
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

void	read_map(t_game *game, char **av)
{	
	int		file;
	char	*line;
	int		x;
	int		y;
	int		z;

	game->fov = 100;
	game->column_size = 5;
	//game->column_size = WIDTH / game->fov;
	//game->ray_step = 1;
	game->ray_step = (float) game->fov / (WIDTH / game->column_size);
	game->tile_size = 50;
	// tex
	game->map.tex[0] = mlx_load_png("./tex.png");
	// sky and floor color
	game->map.col[0] = 0x2E1A47FF;
	game->map.col[1] = 0x1E3226FF;
	// read map.cub file
	x = 50;
	y = 50;
	game->map.map = (int **) malloc(y * sizeof(int *));
	z = -1;
	while (++z < y)
		game->map.map[z] = (int *) malloc(x * sizeof(int));
	y = -1;
	while (++y < 50)
	{
		x = -1;
		while (++x < 50)
			game->map.map[x][y] = -1;
	}
	file = open(av[1], O_RDONLY);
	line = get_next_line(file);
	y = 0;
	while (line)
	{
		printf("%s", line);
		x = -1;
		while (line[++x] && line[x] != '\n')
		{
			game->map.map[x][y] = line[x] - '0';
			if (line[x] == 'N')
			{
				game->map.map[x][y] = 0;
				game->player.pos.x = (float) x * game->tile_size;
				game->player.pos.y = (float) y * game->tile_size;
				game->player.rot = 270;
			}
		}
		y++;
		line = get_next_line(file);
	}
	printf("player (%f, %f)\n", game->player.pos.x, game->player.pos.y);
}

void	draw_cube(t_game *game, t_vector2i start, t_vector2i end, int color)
{
	t_vector2i	v;

	v.x = start.x;
	v.y = start.y;
	while (v.x < end.x)
	{
		mlx_put_pixel(game->img, v.x, v.y, color);
		v.y++;
		if (v.y == end.y)
		{
			v.x++;
			v.y = start.y;
		}
	}
}

void	draw_colum(t_game *game, int x, int faraway, int col)
{
	t_vector2i	a;
	t_vector2i	b;
	int		c;
	int		s;
	int		h;
	int		o;
	unsigned int	xy[2];
	unsigned int	wh[2];

	// column
	s = game->tile_size;
	c = game->column_size;
	h = faraway;
	if (h > HEIGHT / 2)
		h = HEIGHT / 2;
	a.x = x;
	a.y = h;
	b.x = x + c;
	b.y = HEIGHT - h + 1;
	//printf("x = %d, d = %d, h = %d\n",x, faraway, h);
	//printf("a = x = %d, y = %d\n", a.x, a.y);
	//printf("b = x = %d, y = %d\n", b.x, b.y);
	xy[0] = 1;
	xy[1] = 1;
	wh[0] = 5;
	wh[1] = 400;
	//game->map.tex_img[0][x] = mlx_texture_area_to_image(game->mlx, game->map.tex[0], xy, wh);
	//if (mlx_image_to_window(game->mlx, game->map.tex_img[0][x], a.x, a.y) < 0)
    //   return ;
	if (a.x > 0 && a.x < WIDTH - 10 && b.x > 0 && b.y < HEIGHT - 10)
	{
		draw_cube(game, a, b, col);
	//	mlx_draw_texture(game->img, game->map.tex[0], a.x, a.y);
	}
}

void	horizon_ray(t_game *game, t_vector2f *ray, t_vector2f *step, float ray_angel)
{
	t_vector2f	p;
	int			ts;
	float		arctan;

	p = game->player.pos;
	ts = game->tile_size;
	arctan = -1 / tan(ray_angel * DR);
	if (ray_angel > 180)
	{
		ray->y = ((int) p.y / ts) * ts - 0.001;
		ray->x = (p.y - ray->y) * arctan + p.x;
		step->y = -ts;
		step->x = -step->y * arctan;
	}
	else if (ray_angel < 180)
	{
		ray->y = ((int) p.y / ts) * ts + ts;
		ray->x = (p.y - ray->y) * arctan + p.x;
		step->y = ts;
		step->x = -step->y * arctan;
	}
}

void	vertical_ray(t_game *game, t_vector2f *ray, t_vector2f *step, float ray_angel)
{
	t_vector2f	p;
	int			ts;
	float		arctan;

	p = game->player.pos;
	ts = game->tile_size;
	arctan = -tan(ray_angel * DR);
	if (ray_angel > 90 && ray_angel < 270)
	{
		ray->x = ((int) p.x / ts) * ts - 0.001;
		ray->y = (p.x - ray->x) * arctan + p.y;
		step->x = -ts;
		step->y = -step->x * arctan;
	}
	else if (ray_angel < 90 || ray_angel > 270)
	{
		ray->x = ((int) p.x / ts) * ts + ts;
		ray->y = (p.x - ray->x) * arctan + p.y;
		step->x = ts;
		step->y = -step->x * arctan;
	}
}

t_vector2f	cast_rays(t_game *game, int dof, t_vector2f ray, t_vector2f step)
{
	t_vector2f	outray;
	t_vector2i	tile;
	int			ts;

	ts = game->tile_size;
	//outray = ray;
	while (dof > 0)
	{
		tile.x = ray.x / ts;
		tile.y = ray.y / ts;
		if (tile.x >= 0 && tile.y >= 0 && tile.x < 50 && tile.y < 50
				&& game->map.map[tile.x][tile.y] == 1)
		{
			dof = 0;
			outray = ray;
		}
		else
		{
			dof--;
			ray.x += step.x;
			ray.y += step.y;
		}
	}
	return (outray);
}

void	draw_rays(t_game *game, t_vector2f ray)
{
	int			s;
	t_vector2f	pp;
	t_vector2f	r;

	s = 5;
	r.x = ray.x / s;
	r.y = ray.y / s;
	pp.x = game->player.pos.x / s;
	pp.y = game->player.pos.y / s;
	if (r.x > 0 && r.y > 0 && r.x < WIDTH && r.y < HEIGHT)
		draw_line1(game, pp, r);
}

int		distance(t_game *game, t_vector2f hray, t_vector2f vray, float ray_angel)
{
	t_vector2f	ray;
	t_vector2f	d;
	int			ds;
	float		fish;

	fish = game->player.rot - ray_angel;
	d.x = dst(game->player.pos, hray);
	d.y = dst(game->player.pos, vray);
	if (d.x > d.y)
	{
		ds = d.y;
		ray = vray;
	}
	else
	{
		ds = d.x;
		ray = hray;
	}
	ds = ds * cos(fish * DR);
	draw_rays(game, ray);
	return (ds);
}

void	draw_walls2(t_game *game)
{
	t_vector2f	ray;
	t_vector2f	step;
	t_vector2f	vray;
	t_vector2f	hray;
	float		ray_angel;
	int			dof;
	int			ds;
	int			fov;
	int			c;

	c = 0;
	fov = game->fov / 2;
	ray_angel = circle(game->player.rot - (float) fov);
	while (c < WIDTH)
	{
		// horizon
		dof = 50;
		if (ray_angel != 180 && ray_angel != 0)
			horizon_ray(game, &ray, &step, ray_angel);
		else
		{
			ray.x = game->player.pos.x;
			ray.y = game->player.pos.y;
			dof = 0;
		}
		hray = cast_rays(game, dof, ray, step);	
		// vertical
		dof = 50;
		if (ray_angel != 90 && ray_angel != 270)
			vertical_ray(game, &ray, &step, ray_angel);
		else
		{
			ray.x = game->player.pos.x;
			ray.y = game->player.pos.y;
			dof = 0;
		}
		vray = cast_rays(game, dof, ray, step);
		// distance
		ds = distance(game, hray, vray, ray_angel);	
		draw_colum(game, c, ds, 0xAAAA99FF);
		ray_angel += game->ray_step;
		ray_angel = circle(ray_angel);
		c += game->column_size;
	}
	//printf("\n");
}

void	draw_map(t_game *game)
{
	t_vector2i	a;
	t_vector2i	b;
	t_vector2i	i;
	t_vector2f	p1;
	t_vector2f	p2;
	int		t;
	int		scale;

	// map
	scale = 5;
	t = game->tile_size / scale;
	i.y = 0;
	while (i.y < 50)
	{
		i.x = 0;
		while (i.x < 50)
		{
			a.x = i.x * t;
			a.y = i.y * t;
			b.x = (i.x + 1) * t;
			b.y = (i.y + 1) * t;
			//draw_cube(game, a, b, 0xedf2f4ff);
			if (game->map.map[i.x][i.y] == 0)
				draw_cube(game, a, b, 0x8d99aeff);
			if (game->map.map[i.x][i.y] == 1)
				draw_cube(game, a, b, 0x2b2d42ff);
			i.x++;
		}
		i.y++;
	}
	// player
	p1.x = game->player.pos.x / scale;
	p1.y = game->player.pos.y / scale;
	//p1.c = int2rgb(0xffffffff);
	p2.x = game->player.pos.x / scale + cos(game->player.rot * DR) * 5;
	p2.y = game->player.pos.y / scale + sin(game->player.rot * DR) * 5;
	//p2.c = int2rgb(0xffffffff);
	//draw_lineDDA(game, p1, p2);
	draw_line1(game, p1, p2);
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
	draw_cube(game, a, b, game->map.col[0]);
	// floor
	a.x = 0;
	a.y = HEIGHT / 2;
	b.x = WIDTH;
	b.y = HEIGHT;
	draw_cube(game, a, b, game->map.col[1]);
	// walls
	draw_map(game);
	draw_walls2(game);
}

void	render(t_game *game)
{
	int	x;

	mlx_delete_image(game->mlx, game->img);	
	x = -1;
	while (++x < WIDTH / game->column_size)
		mlx_delete_image(game->mlx, game->map.tex_img[0][x]);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	draw_game(game);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		return ;
}

void	hook(void *param)
{
	t_game  	*game;
	float		pdx;
	float		pdy;
	t_vector2i	ptile;
	int			speed;
	int			margin;

	game = (t_game *)param;
	render(game);
	game->player.rot = circle(game->player.rot);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player.rot += 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player.rot -= 1;
	speed = 2;
	margin = 10;
	pdx = cos(game->player.rot * DR) * speed;
	pdy = sin(game->player.rot * DR) * speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		ptile.x = (int) (game->player.pos.x + pdx * margin) / game->tile_size;
		ptile.y = (int) (game->player.pos.y + pdy * margin) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 && ptile.x < 50 && ptile.y < 50
				&& game->map.map[ptile.x][ptile.y] != 1)
		{
			game->player.pos.x += pdx;
			game->player.pos.y += pdy;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		ptile.x = (int) (game->player.pos.x - pdx * margin) / game->tile_size;
		ptile.y = (int) (game->player.pos.y - pdy * margin) / game->tile_size;
		if (ptile.x >= 0 && ptile.y >= 0 && ptile.x < 50 && ptile.y < 50
				&& game->map.map[ptile.x][ptile.y] != 1)
		{
			game->player.pos.x -= pdx;
			game->player.pos.y -= pdy;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		//free(game->p);
	}
}
/*
void movehook(mlx_key_data_t keydata, void* param)
{
	t_game	*game;
	float	pdx;
	float	pdy;

	game = (t_game *) param;
	//if (game->player.rot > 2 * PI)
	//	game->player.rot -= 2 * PI;
	//if (game->player.rot < 0)
	//	game->player.rot += 2 * PI;
	pdx = cos(game->player.rot) * 10;
	pdy = sin(game->player.rot) * 10;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		game->player.rot += DR;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		game->player.rot += DR;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player.pos.x += 10;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		game->player.pos.y += 10;
}
*/
int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
	{
		read_map(&game, av);
		game.mlx = mlx_init(WIDTH, HEIGHT, "mossy rocks", true);
		game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		if (!game.img || mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
			return (0);
		//game.map.tex_img[0] = (mlx_image_t **) malloc((WIDTH / game.column_size + 1)* sizeof(mlx_image_t *));
		//game.map.tex_img[0] = mlx_texture_to_image(game.mlx, game.map.tex[0]);
		//draw_game(&game);
		mlx_loop_hook(game.mlx, hook, &game);
		//mlx_key_hook(game.mlx, &movehook, &game);
		mlx_loop(game.mlx);
		mlx_terminate(game.mlx);
	}
}
