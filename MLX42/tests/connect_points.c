#include "../fdf.h"

void	connect_pointsDDA(mlx_image_t *img, vector3 p1, vector3 p2)
{
	double x;
	double y;
	double dx;
	double dy;
	double s;
	int	i;

	x = p1.x;
	y = p1.y;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	s = dy/dx;
	if (fabs(dx) >= fabs(dy))
		s = fabs(dx);
	else
		s = fabs(dy);
	dx = dx / s;
	dy = dy / s;
	i = 1;
	while (i <= s)
	{
		mlx_put_pixel(img, x, y, 0x00FA0AFF);
		x = x + dx;
		y = y + dy;
		i++;
		//x++;
		//y = s * (x - p1.x)  + p1.y;
	}
}

typedef struct s_plot {
	t_vector2int	v;
	t_vector2int	d;
	t_vector2int	s;
	int				err;
	int				e2;
}	t_plot;

void	plot_line(mlx_image_t *img, t_vector3color p0, t_vector3color p1,
		t_plot l)
{
	while (true)
	{
		if (l.v.x > 5 && l.v.y > 5
			&& l.v.x < (int) img->width - 5 && l.v.y < (int) img->height - 5)
			draw_pixel(img, l.v, p0, p1);
		if (l.v.x == p1.x && l.v.y == p1.y)
			break ;
		l.e2 = 2 * l.err;
		if (l.e2 >= l.d.y)
		{
			if (l.v.x == p1.x)
				break ;
			l.err = l.err + l.d.y;
			l.v.x = l.v.x + l.s.x;
		}
		if (l.e2 <= l.d.x)
		{
			if (l.v.y == p1.y)
				break ;
			l.err = l.err + l.d.x;
			l.v.y = l.v.y + l.s.y;
		}
	}
}

void	draw_line(mlx_image_t *img, t_vector3color p0, t_vector3color p1)
{
	t_plot	l;

	l.v.x = p0.x;
	l.v.y = p0.y;
	l.d.x = abs(p1.x - p0.x);
	if (p0.x < p1.x)
		l.s.x = 1;
	else
		l.s.x = -1;
	l.d.y = -abs(p1.y - p0.y);
	if (p0.y < p1.y)
		l.s.y = 1;
	else
		l.s.y = -1;
	l.err = l.d.x + l.d.y;
	plot_line(img, p0, p1, l);
}
