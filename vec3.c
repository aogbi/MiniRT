/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:58:38 by aogbi             #+#    #+#             */
/*   Updated: 2024/12/12 10:17:06 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

t_vector3	vector_create(double x, double y, double z)
{
	t_vector3	v;

	v = (t_vector3){x, y, z};
	return (v);
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

double	ray_sphere_intersect(t_ray ray, t_sphere sphere)
{
	t_vector3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;

	oc = vector_subtract(ray.origin, sphere.center);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(oc, ray.direction);
	c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0)
		return (t);
	return (-1.0);
}

double	calculate_lighting(t_vector3 point, t_vector3 normal)
{
	t_vector3	light_dir;
	double	intensity;

	light_dir = vector_normalize(vector_create(-1.0, -1.0, -1.0));
	intensity = -vector_dot(normal, light_dir);
	if (intensity > 0)
		return (intensity);
	return (0);
}
