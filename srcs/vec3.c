/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:58:38 by aogbi             #+#    #+#             */
/*   Updated: 2025/01/27 15:23:57 by aogbi            ###   ########.fr       */
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

bool	vector3_equal(t_vector3 a, t_vector3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
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

int	calculate_sphere_lighting(t_vector3 point, t_vector3 normal, t_sphere *sphere,t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	double		intensity;

	light_direction = vector_normalize(vector_subtract(data->info.scenes->light->position,
				point));
	intensity = fabs(vector_dot(normal, light_direction));
	r = (int)((double)((sphere->rgb >> 16) & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* ((double)((data->info.scenes->light->rgb >> 16) & 0xFF) / 255.0));
	g = (int)((double)((sphere->rgb >> 8) & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* ((double)((data->info.scenes->light->rgb >> 8) & 0xFF) / 255.0));
	b = (int)((double)(sphere->rgb & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* ((double)(data->info.scenes->light->rgb & 0xFF) / 255.0));
	return ((r << 16) | (g << 8) | b);
}

int	calculate_plane_lighting(t_vector3 point, t_vector3 normal, t_plane *plane,t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	double		intensity;

	light_direction = vector_normalize(vector_subtract(data->info.scenes->light->position,
				point));
	intensity = vector_dot(normal, light_direction);
	r = (int)(((plane->rgb >> 16) & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* (((data->info.scenes->light->rgb >> 16) & 0xFF) / 255.0));
	g = (int)(((plane->rgb >> 8) & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* (((data->info.scenes->light->rgb >> 8) & 0xFF) / 255.0));
	b = (int)((plane->rgb & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* ((data->info.scenes->light->rgb & 0xFF) / 255.0));
	return ((r << 16) | (g << 8) | b);
}

float spheres_while(t_ray ray, t_sphere *sphere)
{
	float tmp; 
	t_sphere *tmp_sphere = NULL;
	float t = INT_MAX;

	while(sphere)
	{
		tmp = ray_sphere_intersect(ray, sphere);
		if (tmp < t)
		{
			t = tmp;
		}
		sphere = sphere->next;
	}
	return (t);
}

float plane_while(t_ray ray, t_plane *plane)
{
	t_plane *tmp_plane = NULL;
	float t = INT_MAX, tmp;

	while(plane)
	{
		tmp = ray_plane_intersect(ray, *plane);
		if (tmp < t)
		{
			t = tmp;
		}
		plane = plane->next;
	}
	return (t);
}

int	close_intersect(t_data *data, t_ray ray)
{
	int		colore =  0;
	t_sphere	*sphere;
	t_plane		*plane;
	t_vector3	normal;

	sphere = data->info.scenes->sphere;
	float sphere_d = spheres_while(ray, sphere);
	plane = data->info.scenes->plane;
	float plane_d = plane_while(ray, plane);
	t_vector3 hit_point;
	if (sphere_d < plane_d && sphere_d)
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, sphere_d));
		normal = vector_normalize(vector_subtract(hit_point, sphere->center));
		colore = calculate_sphere_lighting(hit_point, normal, sphere, data);
	}
	else if (plane_d)
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, plane_d));
		normal = plane->direction;
		colore = calculate_plane_lighting(hit_point, normal, plane, data);
	}
	return (colore);
}

float	ray_sphere_intersect(t_ray ray, t_sphere *sphere)
{
	t_vector3	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	float		t0;
	float		t1;

	oc = vector_subtract(sphere->center, ray.origin);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(oc, ray.direction);
	c = vector_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0.0)
		return((-b - sqrt(discriminant)) / (2.0f * a));
	return (0.0);
}


