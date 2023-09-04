//header

# include "cub3d.h"

void    resize(int width, int height, void *param)
{
    t_game  *game;

    game = (t_game *)param;
    game->width = width;
    game->height = height;
    //printf("x = %d, y = %d\n", width, height);
    mlx_delete_image(game->mlx, game->img);
    mlx_delete_image(game->mlx, game->map.img);
    //fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    game->img = mlx_new_image(game->mlx, game->width, game->height);
    game->map.img = mlx_new_image(game->mlx, game->width, game->height);
    draw_game(game);
    if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
        return ;
    if (!game->map.img || mlx_image_to_window(game->mlx, game->map.img, 0, 0) < 0)
        return ;
}

void	render(t_game *game)
{
	mlx_delete_image(game->mlx, game->img);
	mlx_delete_image(game->mlx, game->map.img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->map.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	draw_game(game);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		return ;
	if (!game->map.img || (mlx_image_to_window(game->mlx, game->map.img, 0, 0) < 0))
		return ;
}


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

void	read_map(t_game *game, char **av)
{	
	int		file;
	char	*line;
	int		x;
	int		y;
	int		z;

	game->fov = 60;
	game->column_size = 1;
	//game->column_size = WIDTH / game->fov;
	game->tile_size = 50;
	// tex
	game->map.tex[0] = mlx_load_png("./vega.png");
	game->map.tex[1] = mlx_load_png("./tex2.png");
	game->map.tex[2] = mlx_load_png("./tex3.png");
	game->map.tex[3] = mlx_load_png("./tex4.png");
	// sky and floor color
	game->map.col[0] = 0x2E1A47FF;
	game->map.col[1] = 0x1E3226FF;
	// read map.cub file
	game->map.size.x = 50;
	game->map.size.y = 50;
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

void	hooploop(void *param)
{
	t_game *game;
	float	dcos;
	float	dsin;
	int		speed;
	t_vector2f player_pos;
	t_vector2f player_dir;
	t_vector2i	p;

	game = (t_game *)param;
	draw_game(game);
	
	speed = 2;
	// direction
	dcos = cos(game->player.rot * DR) * speed;
	dsin = sin(game->player.rot * DR) * speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.rot++;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.rot--;
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
	game->player.rot = circle(game->player.rot);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void	draw_cube(mlx_image_t *img, t_vector2i start, t_vector2i end, int color)
{
	t_vector2i	v;

	v.x = start.x;
	v.y = start.y;
	while (v.x < end.x)
	{
		if (v.x >= 0 && v.y >= 0 && v.x < img->width && v.y < img->height) 
			mlx_put_pixel(img, v.x, v.y, color);
		v.y++;
		if (v.y == end.y)
		{
			v.x++;
			v.y = start.y;
		}
	}
}

void	draw_map2(t_game *game)
{
	t_vector2i	indx;
	t_vector2i	start;
	t_vector2i	end;
	int	tile;

	tile = game->tile_size / game->map.scale;
	indx.y = -1;
	while (game->map.map[++indx.y])
	{
		start.x = 2;
		end.x = tile;
		indx.x = -1;
		while (game->map.map[indx.y][++indx.x])
		{
			if (game->map.map[indx.y][indx.x] == '1')
				draw_cube(game->map.img, start, end, 0xE86A33ff);
			if (game->map.map[indx.y][indx.x] == '0')
				draw_cube(game->map.img, start, end, 0xF2E3DBff);
			start.x += tile;
			end.x += tile;
		}
		start.y += tile;
		end.y += tile;
	}
}

void	raycasting_2drial(t_game *game, t_vector2f start, t_vector2f end, int clr)
{
	t_vector2f player_pos;
	t_vector2f player_dir;
	float	dcos;
	float	dsin;
	int		speed;
	float	rot = game->player.rot -30;
	int		i = 0;

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
}

void	draw_55t_dial_ray(t_game *game, t_vector2f start, t_vector2f end, int clr)
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

bool draw_texture2(t_game *game, uint32_t h2, t_vector2i a, t_vector2i b, t_ray ray)
{
	mlx_image_t* image;
	mlx_texture_t* texture;
	uint8_t* pixelx;
	uint8_t* pixeli;
	uint32_t i;
	uint32_t j;
	uint32_t z;
	uint32_t z2;
	float	r;
	float	r2;
	float	rx;
	float	ry;
	int		h;

	image = game->img;
	texture = game->map.tex[0];
	//printf("xy = %d, %d\n", xy[0], xy[1]);

	//h = ray.dst;	
	h = (game->tile_size * HEIGHT) / ray.dst;
	r = (float) texture->height / h;
	r2 = (float) texture->width / h;
	//printf("r = %f, r2 = %f, h = %d\n", r, r2, h);
	
	j = 0;
	z2 = 0;
	while (j < game->column_size)
	{
		//rx = (float) z2 * r2;
		rx = 0;
		i = 0;
		z = 0;
		while (i < h2)
		{
			//ry = (float) z / r;
			ry = (float) z * r;
			pixelx = &texture->pixels[(((((int) ry) * texture->width) + (a.x + (int) rx))) * texture->bytes_per_pixel];
			pixeli = &image->pixels[((a.y + i) * image->width + (a.x + j)) * texture->bytes_per_pixel];
			ft_memmove(pixeli, pixelx, texture->bytes_per_pixel);
			i++;
			z++;
			if (ry > texture->height)
				z = 0;
		}
		j++;
		//z2++;	
		//if (rx > texture->width)
		//	z2 = 0;
	}
	return (true);
}

int	draw_colum2(t_game *game, int x, t_ray ray)
{
	t_vector2i	a;
	t_vector2i	b;
	int		c;
	int		s;
	int		h;
	int		o;
	int		h2;

	// column
	s = game->tile_size;
	c = game->column_size;
	h = (ray.dst / 2) + (5000 / ray.dst);
	if (h > HEIGHT)
		h = HEIGHT;
	a.x = x;
	a.y = h ;
	b.x = x + c;
	b.y = HEIGHT - h;
	h2 = b.y - h;
	if (b.y <= a.y)
		b.y = a.y + 1;
	if (h2 <= 1)
		h2 = 1;	
	//printf("h = %f, h2 = %d\n", h, h2);
	//printf("a = %d, %d\n", a.x, a.y);
	//printf("b = %d, %d\n", b.x, b.y);
	if (a.x > 1 && a.x < WIDTH - 1 && a.y > 1 && a.y < HEIGHT - 1
			&& b.x > 1 && b.x < WIDTH - 1 && b.y > 1 && b.y < HEIGHT - 1)
	{	
		// draw_cube(game->img, a, b, 0xCCBBAA);
		draw_texture2(game, h2, a, b, ray);
	}
	return (0);
}
