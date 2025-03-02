/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:18:32 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 01:03:48 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	if (*(str++) == '.')
	{
		while (ft_isdigit(*str))
		{
			decimal = decimal * 10.0f + (float)(*(str++) - '0');
			count++;
		}
	}
	return ((result + decimal / (float)pow(10, count)) * (float)sign);
}

bool	shadow(t_data *data, t_vector3 point, t_vector3 *light_direction)
{
	t_ray	ray;
	float	length;
	float	sphere_d;
	float	plane_d;
	float	cylander_d;

	length = vector_length(*light_direction);
	*light_direction = scale(*light_direction, 1.0f / length);
	ray = (t_ray){point, *light_direction};
	sphere_d = spheres_while(ray, data);
	plane_d = 0;
	plane_d = plane_while(ray, data);
	cylander_d = 0;
	cylander_d = cyl_while(ray, data);
	if ((sphere_d > EPSILON && sphere_d < length) || (plane_d > EPSILON
			&& plane_d < length) || (cylander_d > EPSILON
			&& cylander_d < length))
		return (0);
	return (1);
}
