/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:07:33 by yhachami          #+#    #+#             */
/*   Updated: 2023/07/24 20:09:27 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 1000
# define HEIGHT 720
# define DEFAULT_COLOR "0xFFFFFFFF"
# define PI 3.14159265359
# define P2 1.57079632679
# define P3 4.71238898038
# define DR 0.0174533

typedef struct s_rgb {
        int     r;
        int     g;
        int     b;
        int     a;
}       t_rgb;

typedef struct s_v3c {
        int             x;
        int             y;
        int             z;
        t_rgb   c;
}       t_vector3color;

typedef struct s_v3i {
        int   x;
        int   y;
        int   z;
}       t_vector3i;

typedef struct s_v3 {
        float   x;
        float   y;
        float   z;
}       t_vector3f;

typedef struct s_v2i {
        int     x;
        int     y;
}       t_vector2i;

typedef struct s_v2 {
        float     x;
        float     y;
}       t_vector2f;

typedef struct s_plot {
        t_vector2i	v;
        t_vector2i	d;
        t_vector2i	s;
        int		err;
        int		e2;
}       t_plot;

typedef struct	s_map {
	int	**map;
	int	tex[4];
	int	col[2];
}		t_map;

typedef	struct	s_player {
	t_vector2f	pos;
	float		rot;
}		t_player;

typedef struct s_game {
	t_map		map;
        t_player	player;
	int		tile_size;
	int		column_size;
	int		fov;
	mlx_t                   *mlx;
        mlx_image_t             *img;
        mlx_image_t             *ui[30];
}               t_game;

char	*get_next_line(int fd);
char	*ft_itoa(int n);
int	ft_atoi(char *str);
int	ft_strlen(const char *s);
void	draw_lineDDA(t_game *game, t_vector3color p1, t_vector3color p2);
void	draw_line1(t_game *game, t_vector2f p1, t_vector2f p2);
t_rgb	int2rgb(long long int mono);
int	rgb2int(t_rgb c);

#endif
