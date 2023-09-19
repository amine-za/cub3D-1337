/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaghlou <azaghlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 02:13:11 by yhachami          #+#    #+#             */
/*   Updated: 2023/09/01 23:22:54 by azaghlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	count_digits(int nb)
{
	int	digits;

	digits = 1;
	if (nb < 0)
	{
		nb *= -1;
		digits++;
	}
	while (nb > 9 && ++digits > 0)
		nb /= 10;
	return (digits);
}

static void	nega(int *n, char *s)
{
	if (*n == 0)
		s[0] = '0';
	if (*n < 0)
	{
		*n *= -1;
		s[0] = '-';
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		digits;
	int		max;

	max = 0;
	if (n == -2147483648)
	{
		max = 1;
		n = -214748364;
	}
	digits = count_digits(n);
	str = (char *)malloc(digits + max + 1);
	if (!str)
		return (0);
	nega(&n, str);
	i = 0;
	while (n > 0)
	{
		str[digits - (++i)] = n % 10 + '0';
		n /= 10;
	}
	str[digits] = '8';
	str[digits + max] = '\0';
	return (str);
}
