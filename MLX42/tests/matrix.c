#include"fdf.h"

// | x.x  x.y  x.z |   | p.x |     | pro.x |

// | y.x  y.y  y.z | * | p.y |  =  | pro.y |

// | z.x  z.y  z.z |   | p.z |     | pro.z |

void	enter_the_matrix(t_vars *vars, int i, int j)
{
	t_vector3 		x;
	t_vector3 		y;
	t_vector3 		z;
	t_vector3color	p;
	t_vector3 		s;
	t_vector3 		r;

	r = vars->grid_rot;
	s = vars->grid_shift;
	p = vars->p[i][j];
	x.x = cos(r.x) * sin(r.y);
	x.y = cos(r.x) * sin(r.y) * sin(r.z) - sin(r.x) * cos(r.y);
	x.z = cos(r.x) * sin(r.y) * cos(r.z) + sin(r.x) * sin(r.y);
	y.x = sin(r.x) * cos(r.y);
	y.y = sin(r.x) * sin(r.y) * sin(r.z) + cos(r.x) * cos(r.y);
	y.z = sin(r.x) * sin(r.y) * cos(r.z) - cos(r.x) * sin(r.y);
	z.x = -sin(r.y);
	z.y = cos(r.y) * sin(r.z);
	z.z = cos(r.y) * cos(r.z);
	vars->pro[i][j].x = (s.x * p.x) * x.x + (s.y * p.y) * x.y + (s.z * p.z) * x.z;
	vars->pro[i][j].y = (s.x * p.x) * y.x + (s.y * p.y) * y.y + (s.z * p.z) * y.z;
	vars->pro[i][j].z = (s.x * p.x) * z.x + (s.y * p.y) * z.y + (s.z * p.z) * z.z;
	// vars->pro[i][j].z = p.z;
	vars->pro[i][j].c = p.c;
}

void	red_pill(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < vars->grid_size.y)
	{
		enter_the_matrix(vars, i, j);
		i++;
		if (i == vars->grid_size.x)
		{
			j++;
			i = 0;
		}
	}
}

void	project_grid(t_vars *vars)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < vars->grid_size.y)
	{
		vars->pro[i][j].x = vars->grid_start.x - vars->pro[i][j].z;
		vars->pro[i][j].y = vars->grid_start.y - vars->pro[i][j].z;
		i++;
		if (i == vars->grid_size.x)
		{
			j++;
			i = 0;
		}
	}
}

int	draw_grid(t_vars *vars)
{
	int	i;
	int	j;

	redpill(vars);
	project_grid(vars);
	i = 0;
	j = 0;
	while (j < vars->grid_size.y)
	{
		if (i < vars->grid_size.x -1)
			connect_points(vars->img, vars->pro[i][j], vars->pro[i +1][j]);
		if (j < vars->grid_size.y -1)
			connect_points(vars->img, vars->pro[i][j], vars->pro[i][j +1]);
		i++;
		if (i == vars->grid_size.x)
		{
			j++;
			i = 0;
		}
	}
	return (0);
}