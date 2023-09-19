/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:07:33 by yhachami          #+#    #+#             */
/*   Updated: 2023/09/19 19:25:40 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "utils/get_next_line.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720
# define PI 3.14159265359
# define DR 0.0174533

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_rgb;

typedef struct s_v3i
{
	int				x;
	int				y;
	int				z;
}					t_vector3i;

typedef struct s_v3
{
	float			x;
	float			y;
	float			z;
}					t_vector3f;

typedef struct s_v2i
{
	int				x;
	int				y;
}					t_vector2i;

typedef struct s_v2
{
	float			x;
	float			y;
}					t_vector2f;

typedef struct s_map
{
	mlx_image_t		*img;
	t_vector2i		size;
	float			scale;
	char			**map;
	long int		col[2];
	mlx_texture_t	*tex[4];
	mlx_image_t		*tex_img[4];
}					t_map;

typedef struct s_player
{
	t_vector2f		pos;
	t_vector2f		img_pos;
	t_vector2f		img_mult;
	float			rot;
	mlx_texture_t	*tex;
	mlx_image_t		*img;
}					t_player;

typedef struct s_ray
{
	t_vector2f		ray;
	t_vector2f		step;
	t_vector2i		tile;
	t_vector2f		pos_in_tile;
	float			angel_step;
	float			dst;
	float			wall_height;
	float			angel;
	int				dof;
}					t_ray;

typedef struct s_game
{
	t_map			map;
	t_player		player;
	t_vector2i		window;
	int				tile_size;
	int				column_size;
	int				fov;
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	mlx_t			*mlx;
}					t_game;

char	*get_next_line(int fd);
char	*ft_itoa(int n);
int		ft_atoi(char *str);
void	*ft_memmove(void *dst, void *src, size_t len);
char	*ft_strdup(char *s1);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_bzero(void *s, size_t n);

t_rgb	int2rgb(long long int mono);
int		rgb2int(t_rgb c);
int		parsing_main(t_game *game, char *map);
int		map_check(int fd, t_game *game);
void	free_arr(char **ar);
int		rgb2int(t_rgb c);
float	circle(float fish);
float	pythagoras(float a, float b);

void	move_up(t_game *game, t_vector2f pd);
void	move_down(t_game *game, t_vector2f pd);
void	move_right(t_game *game, t_vector2f pd);
void	move_left(t_game *game, t_vector2f pd);

void	draw_circle(mlx_image_t *img, t_vector2i center, int r, int clr);
void	draw_rays(t_game *game, t_vector2f ray, int clr);
void	draw_cube(mlx_image_t *img, t_vector2i start, t_vector2i end,
			int color);
void	draw_line(mlx_image_t *img, t_vector2f p0, t_vector2f p1, int clr);
void	draw_texture(t_game *game, t_ray ray, t_vector2i a);
void	player_to_image(t_game *game, t_vector2i img_pos, float sx, float sy);
void	draw_player(t_game *game);
void	draw_colum(t_game *game, int x, t_ray ray);
void	draw_walls(t_game *game);
void	draw_game(t_game *game);
void	draw_map(t_game *game);

int		space_tabe(char c);
int		ft_isdigit(int c);
int		rgb_check(char *rgb);
int		space_tabe(char c);
int		finished_that_check(int *result, char *line);
void	fill_int_arry_with_zero(int *result);
int		clrs(char *line, int indx, int *result, t_game *game);
void	free_arr(char **ar);
int		tallest_line_length(char **map);
char	**arrjoin(char **ar, char *line, int size);
int		check_line(char *line);
void	calloc_the_array(char ***ar, char *rgb, char **pntr);
int		exist_char(char *str, int indx);

#endif
