/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:58:38 by aogbi             #+#    #+#             */
/*   Updated: 2025/01/08 11:58:26 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3	vector_create(double x, double y, double z)
{
	t_vector3	v;

	v = (t_vector3){x, y, z};
	return (v);
}

t_vector3	vector_add(t_vector3 a, t_vector3 b)
{
	return ((t_vector3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector3	vector_subtract(t_vector3 v1, t_vector3 v2)
{
	return (vector_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

double	vector_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	vector_normalize(t_vector3 v)
{
	double	length;

	length = sqrt(vector_dot(v, v));
	return (vector_create(v.x / length, v.y / length, v.z / length));
}

t_vector3	scale(t_vector3 v, float scalar)
{
	return (vector_create(v.x * scalar, v.y * scalar, v.z * scalar));
}

bool vector3_equal(t_vector3 a, t_vector3 b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}

// double	calculate_lighting(t_vector3 normal, t_data *data)
// {
// 	double		intensity;

// 	intensity = -vector_dot(normal, data->info.scenes->light->position);
// 	if (intensity > 0)
// 		return (intensity);
// 	return (0);
// }

t_vector3	ray_sphere_intersect(t_ray ray, t_sphere *sphere)
{
	t_vector3	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vector_subtract(sphere->center, ray.origin);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(oc, ray.direction);
	c = vector_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0.0)
	{
		float t0 = (-b - sqrt(discriminant)) / (2.0f * a);
		float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
		if (t0 < t1)
			return (vector_add(ray.origin, scale(ray.direction, t0)));
		else
			return (vector_add(ray.origin, scale(ray.direction, t1)));
	}
	return ((t_vector3){0});
}
