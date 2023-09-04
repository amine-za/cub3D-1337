/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 05:04:34 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/31 05:08:51 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	pythagoras(float a, float b)
{
	return (sqrt((a * a) + (b * b)));
}

float	circle(float fish)
{
	if (fish >= 360)
		fish -= 360;
	if (fish < 0)
		fish += 360;
	return (fish);
}
