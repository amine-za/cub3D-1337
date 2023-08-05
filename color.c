/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:25:38 by yhachami          #+#    #+#             */
/*   Updated: 2023/07/24 20:08:59 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

int	find_end(char *s)
{
	int	i;

	i = 0;
	while (s[i] != ' ' && s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

t_rgb	int2rgb(long long int mono)
{
	t_rgb	color;

	if (mono > 0xFFFFFF)
	{
		color.r = (mono >> 24) & 0xFF;
		color.g = (mono >> 16) & 0xFF;
		color.b = (mono >> 8) & 0xFF;
		color.a = mono & 0xFF;
	}
	else
	{
		color.r = (mono >> 16) & 0xFF;
		color.g = (mono >> 8) & 0xFF;
		color.b = mono & 0xFF;
		color.a = 255;
	}
	return (color);
}

int	rgb2int(t_rgb c)
{
	return (c.r << 24 | c.g << 16 | c.b << 8 | c.a);
}

int	get_chanel(char *s)
{
	int	i;
	int	v;
	int	base;

	i = find_end(s);
	v = 0;
	base = 1;
	while (--i >= 0)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			v += (s[i] - 55) * base;
		if (s[i] >= 'a' && s[i] <= 'z')
			v += (s[i] - 87) * base;
		else if (s[i] >= '0' && s[i] <= '9')
			v += (s[i] - '0') * base;
		base *= 16;
	}
	return (v);
}

t_rgb	get_color(char *s)
{
	long long int	mono;

	if (s[0] == '0' && s[1] == 'x')
		mono = get_chanel(s + 2);
	else
		mono = get_chanel("FFFFFF");
	return (int2rgb(mono));
}
