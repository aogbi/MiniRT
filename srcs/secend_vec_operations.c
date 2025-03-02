/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secend_vec_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:58:38 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:17:31 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3	vector_create(float x, float y, float z)
{
	t_vector3	v;

	v = (t_vector3){x, y, z};
	return (v);
}

t_vector3	scale(t_vector3 v, float scalar)
{
	return (vector_create(v.x * scalar, v.y * scalar, v.z * scalar));
}

bool	vector3_equal(t_vector3 a, t_vector3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

float	vector_length(t_vector3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
