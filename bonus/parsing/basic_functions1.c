/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:22:05 by azaghlou          #+#    #+#             */
/*   Updated: 2023/09/04 18:09:06 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// A function that take an int array and fill it with zeros
void	fill_int_arry_with_zero(int *result)
{
	result[0] = 0;
	result[1] = 0;
	result[2] = 0;
	result[3] = 0;
	result[4] = 0;
	result[5] = 0;
	result[6] = 0;
}

// A function that check if the character given is a space or tabe
int	space_tabe(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// A function that checks if i finished checking the textures and rgb lines
int	finished_that_check(int *result, char *line)
{
	if (!line)
		return (0);
	if (result[0] == 1 && result[1] == 1 && result[2] == 1 && result[3] == 1
		&& result[4] == 1 && result[5] == 1)
		return (1);
	return (0);
}

/* A function that a string with an index and check if 
that string with that index and that index plus one exist */
int	exist_char(char *str, int indx)
{
	if (str && str[indx] && str[indx])
		return (1);
	return (0);
}
