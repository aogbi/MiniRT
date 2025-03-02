/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:20:25 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:34:23 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3	quadratic_equation(t_ray ray, t_cylinder *cyl)
{
	t_vector3	oc;
	t_vector3	d_cross_v;
	t_vector3	oc_cross_v;
	t_vector3	equa;

	oc = vector_subtract(ray.origin, cyl->center);
	d_cross_v = vector_cross(ray.direction, cyl->axis);
	oc_cross_v = vector_cross(oc, cyl->axis);
	equa.x = vector_dot(d_cross_v, d_cross_v);
	equa.y = 2 * vector_dot(oc_cross_v, d_cross_v);
	equa.z = vector_dot(oc_cross_v, oc_cross_v) - (cyl->radias * cyl->radias);
	return (equa);
}

float	ray_plane_intersect(t_ray ray, t_plane plane)
{
	float		denom;
	t_vector3	p0_to_origin;
	float		t;

	denom = vector_dot(plane.direction, ray.direction);
	if (!denom)
		return (0);
	p0_to_origin = vector_subtract(plane.position, ray.origin);
	t = vector_dot(p0_to_origin, plane.direction) / denom;
	if (t > 0)
		return (t);
	return (0);
}

bool	hit_cord(t_vector3 equa, float *t1, float *t2)
{
	float		delta;

	delta = equa.y * equa.y - 4 * equa.x * equa.z;
	if (delta < 0)
		return (false);
	*t1 = (-equa.y - sqrt(delta)) / (2 * equa.x);
	*t2 = (-equa.y + sqrt(delta)) / (2 * equa.x);
	return (true);
}

float	intersect_cylinder(t_ray ray, t_cylinder *cyl)
{
	t_vector3	equa;
	float		t1;
	float		t2;
	float		h1;
	float		h2;

	equa = quadratic_equation(ray, cyl);
	if (!hit_cord(equa, &t1, &t2))
		return (0);
	h1 = vector_dot(vector_subtract(vector_add(ray.origin, scale(ray.direction,
						t1)), cyl->center), cyl->axis);
	h2 = vector_dot(vector_subtract(vector_add(ray.origin, scale(ray.direction,
						t2)), cyl->center), cyl->axis);
	if (0 <= h1 && h1 <= cyl->height)
		return (t1);
	else if (0 <= h2 && h2 <= cyl->height)
		return (t2);
	return (-1);
}

float	ray_sphere_intersect(t_ray ray, t_sphere *sphere)
{
	t_vector3	oc;
	t_vector3	equa;
	float		discriminant;

	oc = vector_subtract(ray.origin, sphere->center);
	equa.x = vector_dot(ray.direction, ray.direction);
	equa.y = 2.0f * vector_dot(oc, ray.direction);
	equa.z = vector_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = equa.y * equa.y - 4.0f * equa.x * equa.z;
	if (discriminant >= 0.0f)
		return ((-equa.y - sqrt(discriminant)) / (2.0f * equa.x));
	return (0.0f);
}
