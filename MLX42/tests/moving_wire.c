// SRC = MLX42/fdf_test/moving_wire.c draw_line.c color.c
#include"../../fdf.h"

void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	draw(t_vars *vars)
{
	int i;

	i = 0;
	while (i < 3)
	{
		vars->p[0][i].c = get_color("0xFFFFFFFF");
		vars->p[0][i + 1].c = get_color("0xBB0A1EFF");
		vars->p[0][i].x = vars->grid_start.x + sin((vars->grid_rot.x + i) / 10) * vars->grid_shift.x + sin((vars->grid_rot.x + i)) * 50;
		vars->p[0][i].y = vars->grid_start.y + cos((vars->grid_rot.y + i) / 10) * vars->grid_shift.x;
		vars->p[0][i+ 1].x = vars->grid_start.x + sin((vars->grid_rot.x + i) / 5) * vars->grid_shift.y + sin((vars->grid_rot.x + i)) *100;
		vars->p[0][i+ 1].y = vars->grid_start.y + cos((vars->grid_rot.y + i) / 5) * vars->grid_shift.y;
		draw_line(vars->img, vars->p[0][i], vars->p[0][i + 1]);
		i++;
	}
	vars->grid_start.x++;
	vars->grid_rot.x++;
	vars->grid_rot.y++;
	if (vars->grid_start.x >= 1000)
	{
		vars->grid_shift.y -= 5;
		vars->grid_shift.x -= 10;
		vars->index = 1;
	}
}

void	draw_back(t_vars *vars)
{
	int i;

	i = 0;
	while (i < 3)
	{
		vars->p[0][i].c = get_color("0xFFFFFFFF");
		vars->p[0][i + 1].c = get_color("0x0ABB1EFF");
		vars->p[0][i].x = vars->grid_start.x + sin((vars->grid_rot.x + i) / 10) * vars->grid_shift.x - sin((vars->grid_rot.x + i)) * 50;
		vars->p[0][i].y = vars->grid_start.y + cos((vars->grid_rot.y + i) / 10) * vars->grid_shift.x;
		vars->p[0][i+ 1].x = vars->grid_start.x + sin((vars->grid_rot.x + i) ) * vars->grid_shift.y  - sin((vars->grid_rot.x + i));
		vars->p[0][i+ 1].y = vars->grid_start.y + cos((vars->grid_rot.y + i) ) * vars->grid_shift.y;
		draw_line(vars->img, vars->p[0][i], vars->p[0][i + 1]);
		i++;
	}
	vars->grid_start.x--;
	vars->grid_rot.x--;
	vars->grid_rot.y--;
	if (vars->grid_start.x <= 300)
	{
		vars->grid_shift.y += 5;
		vars->grid_shift.x += 10;
		vars->index = 0;
	}
}

void	render(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (vars->index == 0)
		draw(vars);
	else if (vars->index == 1)
		draw_back(vars);
	if (!vars->img || (mlx_image_to_window(vars->mlx, vars->img, 0, 0) < 0))
		ft_error();
}

void hook(void* param)
{
	t_vars *vars = param;
	
	render(vars);

	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
}

int main(int argc , char **argv)
{
	// printf("---------------MoW-----------------\n");
	if (argc == 1)
		printf("thanks for nothing\n");
	else 
		printf("fuck off %d, dont need no %s shit from nobody\n",argc,argv[1]);
	
	t_vars	vars;
	vars.grid_size.x = 5;
	vars.grid_size.y = 5;
	vars.grid_start.x = 500;
	vars.grid_start.y = 500;
	vars.grid_shift.x = 100;
	vars.grid_shift.y = 100;
	vars.grid_rot.x = 10;
	vars.grid_rot.y = 10;
	vars.index = 0;
	
	vars.mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!vars.mlx)
		ft_error();

	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.img || (mlx_image_to_window(vars.mlx, vars.img, 0, 0) < 0))
		ft_error();

	vars.p = (t_vector3color **) malloc(vars.grid_size.x * sizeof(t_vector3color *));
	int y = -1;
	while (++y < vars.grid_size.x)
		vars.p[y] = (t_vector3color *) malloc(vars.grid_size.y * sizeof(t_vector3color));
	
	// int i = 100;
	// int j = 100;
	// float t = 250;
	// while (t < 700)
	// {
	// 	connect_pointsDDA(vars.img, vars.pr[0], vars.pr[1]);
	// 	// mlx_put_pixel(vars.img, i, j, 0xBB0A1EAA);
	// 	t++;
	// 	vars.pr[0].x = t + sin(t / 10) * 100  + sin(t ) * 50;
	// 	vars.pr[0].y = t + cos(t / 10) * 100;
	// 	vars.pr[1].x = t + sin(t / 10) * 100  + sin(t /20) * 20;
	// 	vars.pr[1].y = t + cos(t / 10) * 100;
	// }

	mlx_loop_hook(vars.mlx, hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
	return 0;
}