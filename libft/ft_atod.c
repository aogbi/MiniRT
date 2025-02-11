/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:44:43 by aogbi             #+#    #+#             */
/*   Updated: 2025/02/10 19:16:25 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atod(char *str)
{
	float	result;
	float	decimal;
	int		count;
	int		sign;

	result = 0.0f;
	decimal = 0.0f;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		result = result * 10.0f + (float)(*str++ - '0');
	count = 0;
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			decimal = decimal * 10.0f + (float)(*str - '0');
			str++;
			count++;
		}
	}
	return ((result + decimal / (float)pow(10, count)) * (float)sign);
}
