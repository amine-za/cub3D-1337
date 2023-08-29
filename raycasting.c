

#include"cub3d.h"

int	draw_colum(t_game *game, int x, t_ray ray)
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
	h = (game->tile_size * HEIGHT) /ray.dst;
	if (h > HEIGHT)
		h = HEIGHT;
	a.x = x;
	a.y = (HEIGHT / 2) - (h / 2);
	b.x = x + c;
	b.y = (HEIGHT / 2) + (h / 2);
	h2 = h;

	if (a.y < 5)
		a.y = 5;
	if (b.y > HEIGHT - 5)
		b.y = HEIGHT - 5;
	if (a.x > 0 && a.x < WIDTH && a.y > 0 && a.y < HEIGHT
			&& b.x > 0 && b.x < WIDTH && b.y > 0 && b.y < HEIGHT)
	{	
		draw_cube(game->img, a, b, 0xAAAAAAFF);
		draw_texture(game, h2, a, ray);
	}
	return (0);
}

void	horizon_ray(t_game *game, t_ray *ray)
{
	t_vector2f	p;
	int			ts;
	float		arctan;

	p = game->player.pos;
	ts = game->tile_size;
	arctan = -1 / tan(ray->angel * DR);
	if (ray->angel > 180)
	{
		ray->ray.y = ((int) p.y / ts) * ts - 0.001;
		ray->ray.x = (p.y - ray->ray.y) * arctan + p.x;
		ray->step.y = -ts;
		ray->step.x = -ray->step.y * arctan;
	}
	else if (ray->angel < 180)
	{
		ray->ray.y = ((int) p.y / ts) * ts + ts;
		ray->ray.x = (p.y - ray->ray.y) * arctan + p.x;
		ray->step.y = ts;
		ray->step.x = -ray->step.y * arctan;
	}
}

void	vertical_ray(t_game *game, t_ray *ray)
{
	t_vector2f	p;
	int			ts;
	float		arctan;

	p = game->player.pos;
	ts = game->tile_size;
	arctan = -tan(ray->angel * DR);
	if (ray->angel > 90 && ray->angel < 270)
	{
		ray->ray.x = ((int) p.x / ts) * ts - 0.001;
		ray->ray.y = (p.x - ray->ray.x) * arctan + p.y;
		ray->step.x = -ts;
		ray->step.y = -ray->step.x * arctan;
	}
	else if (ray->angel < 90 || ray->angel > 270)
	{
		ray->ray.x = ((int) p.x / ts) * ts + ts;
		ray->ray.y = (p.x - ray->ray.x) * arctan + p.y;
		ray->step.x = ts;
		ray->step.y = -ray->step.x * arctan;
	}
}

t_vector2f	cast_rays(t_game *game, int dof, t_ray *ray)
{
	t_vector2f	outray;
	t_vector2i	tile;
	int			ts;

	ts = game->tile_size;
	//outray = ray;
	while (dof > 0)
	{
		ray->tile.x = ray->ray.x / ts;
		ray->tile.y = ray->ray.y / ts;
		if (ray->tile.x >= 0 && ray->tile.y >= 0 && ray->tile.x < game->map.size.x && ray->tile.y < game->map.size.y
				&& game->map.map[ray->tile.y][ray->tile.x] == '1')
		{
			dof = 0;
			outray = ray->ray;
		}
		else
		{
			dof--;
			ray->ray.x += ray->step.x;
			ray->ray.y += ray->step.y;
		}
	}
	return (outray);
}

int		distance(t_game *game, t_vector2f hray, t_vector2f vray, t_ray *ray)
{
	t_vector2f	d;
	float		fish;

	fish = game->player.rot - ray->angel;
	d.x = dst(game->player.pos, hray);
	d.y = dst(game->player.pos, vray);
	if (d.x > d.y)
	{
		ray->dst = d.y;
		ray->ray = vray;
	}
	else
	{
		ray->dst = d.x;
		ray->ray = hray;
	}
	ray->tile.x = ray->ray.x / game->tile_size;
	ray->tile.y = ray->ray.y / game->tile_size;
	ray->dst = ray->dst * cos(fish * DR);
	draw_rays(game, ray->ray);
	return (ray->dst);
}

void	draw_walls(t_game *game)
{
	t_ray		ray;
	t_vector2f	vray;
	t_vector2f	hray;
	int			dof;
	int			c;

	c = 0;
	//c = WIDTH / 2;
	ray.angel_step = (float) game->fov / (WIDTH / game->column_size);
	ray.angel = circle(game->player.rot - (float) game->fov / 2);
	while (c < WIDTH)
	//while (c <= WIDTH / 2)
	{
		// horizon
		dof = 50;
		if (ray.angel != 180 && ray.angel != 0)
			horizon_ray(game, &ray);
		else
		{
			ray.ray.x = game->player.pos.x;
			ray.ray.y = game->player.pos.y;
			dof = 0;
		}
		hray = cast_rays(game, dof, &ray);	
		// vertical
		dof = 50;
		if (ray.angel != 90 && ray.angel != 270)
			vertical_ray(game, &ray);
		else
		{
			ray.ray.x = game->player.pos.x;
			ray.ray.y = game->player.pos.y;
			dof = 0;
		}
		vray = cast_rays(game, dof, &ray);
		// distance
		distance(game, hray, vray, &ray);
		draw_colum(game, c, ray);
		ray.angel = circle(ray.angel + ray.angel_step);
		c += game->column_size;
	}
	//printf("\n");
}