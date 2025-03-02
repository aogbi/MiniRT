/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:15:18 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:16:17 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3	vector_add(t_vector3 a, t_vector3 b)
{
	return ((t_vector3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector3	vector_subtract(t_vector3 v1, t_vector3 v2)
{
	return (vector_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

float	vector_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	vector_cross(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vector3	vector_normalize(t_vector3 v)
{
	float	length;

	length = sqrt(vector_dot(v, v));
	return (vector_create(v.x / length, v.y / length, v.z / length));
}
