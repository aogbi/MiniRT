/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:44:43 by aogbi             #+#    #+#             */
/*   Updated: 2025/01/03 10:40:14 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *str)
{
	double	result;
	double	decimal;
	int		count;
	int		sign;

	result = 0;
	decimal = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	count = 0;
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			decimal = decimal * 10 + (*str - '0');
			str++;
			count++;
		}
	}
	return ((result + decimal / pow(10, count)) * sign);
}
