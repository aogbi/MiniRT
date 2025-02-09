/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:58:38 by aogbi             #+#    #+#             */
/*   Updated: 2025/02/09 16:25:12 by aogbi            ###   ########.fr       */
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

int	calculate_sphere_lighting(t_vector3 point, t_sphere *sphere, t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	double		intensity;

	light_direction = vector_normalize(vector_subtract(point,
				data->info.scenes->light->position));
	intensity = fmax(0.0, -vector_dot(vector_normalize(vector_subtract(point, sphere->center)), light_direction))
		* data->info.scenes->light->brightness_ratio;
	intensity += data->info.scenes->ambient->ratio;
	intensity = fmin(1.0, intensity);
	r = (int)((double)((sphere->rgb >> 16) & 0xFF) * intensity);
	g = (int)((double)((sphere->rgb >> 8) & 0xFF) * intensity);
	b = (int)((double)((sphere->rgb) & 0xFF) * intensity);
	r *= (int)((double)((((data->info.scenes->ambient->rgb >> 16) & 0xFF) / 255)
				* (((data->info.scenes->light->rgb >> 16) & 0xFF) / 255)));
	g *= (int)((double)((((data->info.scenes->ambient->rgb >> 8) & 0xFF) / 255)
				* (((data->info.scenes->light->rgb >> 8) & 0xFF) / 255)));
	b *= (int)((double)(((data->info.scenes->ambient->rgb & 0xFF) / 255)
				* ((data->info.scenes->light->rgb & 0xFF) / 255)));
	return ((r << 16) | (g << 8) | b);
}

int	calculate_plane_lighting(t_vector3 point, t_plane *plane,
		t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	double		intensity;

	light_direction = vector_normalize(vector_subtract(data->info.scenes->light->position,
				point));
	intensity = fmax(0.0, vector_dot(plane->direction, light_direction))
		* data->info.scenes->light->brightness_ratio;
	intensity += data->info.scenes->ambient->ratio;
	intensity = fmin(1.0, intensity);
	r = (int)((double)((plane->rgb >> 16) & 0xFF) * intensity);
	g = (int)((double)((plane->rgb >> 8) & 0xFF) * intensity);
	b = (int)((double)((plane->rgb) & 0xFF) * intensity);
	r *= (int)((double)((((data->info.scenes->ambient->rgb >> 16) & 0xFF) / 255)
				* (((data->info.scenes->light->rgb >> 16) & 0xFF) / 255)));
	g *= (int)((double)((((data->info.scenes->ambient->rgb >> 8) & 0xFF) / 255)
				* (((data->info.scenes->light->rgb >> 8) & 0xFF) / 255)));
	b *= (int)((double)(((data->info.scenes->ambient->rgb & 0xFF) / 255)
				* ((data->info.scenes->light->rgb & 0xFF) / 255)));
	return ((r << 16) | (g << 8) | b);
}

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

double	intersect_cylinder(t_ray ray, t_cylinder *cyl)
{
	t_vector3	equa;
	double		delta;
	double		t1;
	double		t2;
	double		h1;
	double		h2;

	equa = quadratic_equation(ray, cyl);
	delta = equa.y * equa.y - 4 * equa.x * equa.z;
	if (delta < 0)
		return (0);
	t1 = (-equa.y - sqrt(delta)) / (2 * equa.x);
	t2 = (-equa.y + sqrt(delta)) / (2 * equa.x);
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

int	calculate_cylinder_lighting(t_vector3 point, t_cylinder *cyl, t_data *data)
{
	t_vector3	proj;
	t_vector3	normal;
	t_vector3	light_dir;
	double		intensity;
	int			r;
	int			g;
	int			b;

	proj = vector_add(cyl->center, scale(cyl->axis,
				vector_dot(vector_subtract(point, cyl->center), cyl->axis)));
	normal = vector_normalize(vector_subtract(point, proj));
	light_dir = vector_normalize(vector_subtract(data->info.scenes->light->position,
				point));
	intensity = fmax(0.0, vector_dot(normal, light_dir))
		* data->info.scenes->light->brightness_ratio;
	intensity += data->info.scenes->ambient->ratio;
	intensity = fmin(1.0, intensity);
	r = fmin(255, fmax(0, (int)((double)((cyl->rgb >> 16) & 0xFF)
					* intensity)));
	g = fmin(255, fmax(0, (int)((double)((cyl->rgb >> 8) & 0xFF) * intensity)));
	b = fmin(255, fmax(0, (int)((double)(cyl->rgb & 0xFF) * intensity)));
	return ((r << 16) | (g << 8) | b);
}

float	spheres_while(t_ray ray, t_data *data)
{
	float		tmp;
	t_sphere 	*sphere;
	float		t;

	t = 0;
	data->info.save.sphere = NULL;
	sphere = data->info.scenes->sphere;
	if (sphere)
	{
		t = fmax(0.0f, ray_sphere_intersect(ray, sphere));
		data->info.save.sphere = sphere;
		sphere = sphere->next;
	}
	while (sphere)
	{
		tmp = fmax(0.0f, ray_sphere_intersect(ray, sphere));
		if (tmp > 0.0f && (t == 0.0f || tmp < t))
		{
			t = tmp;
			data->info.save.sphere = sphere;
		}
		sphere = sphere->next;
	}
	return (t);
}

float	plane_while(t_ray ray, t_data *data)
{
	float		tmp;
	t_plane	*plane;
	float		t;

	data->info.save.plane = NULL;
	plane = data->info.scenes->plane;
	t = 0;
	if (plane)
	{
		t = fmax(0.0f, ray_plane_intersect(ray, *plane));
		data->info.save.plane = plane;
		plane = plane->next;
	}
	while (plane)
	{
		tmp = fmax(0.0f, ray_plane_intersect(ray, *plane));
		if (tmp > 0.0f && (t == 0.0f || tmp < t))
		{
			t = tmp;
			data->info.save.plane = plane;
		}
		plane = plane->next;
	}
	return (t);
}

float	cyl_while(t_ray ray, t_data *data)
{
	float		tmp;
	t_cylinder	*cyl;
	float		t;

	data->info.save.cylinder = NULL;
	cyl = data->info.scenes->cylinder;
	t = 0;
	if (cyl)
	{
		t = fmax(0.0f, intersect_cylinder(ray, cyl));
		data->info.save.cylinder = cyl;
		cyl = cyl->next;
	}
	while (cyl)
	{
		tmp = fmax(0.0f, intersect_cylinder(ray, cyl));
		if (tmp > 0.0f && (t == 0.0f || tmp < t))
		{
			t = tmp;
			data->info.save.cylinder = cyl;
		}
		cyl = cyl->next;
	}
	return (t);
}

int	close_intersect(t_data *data, t_ray ray)
{
	float		sphere_d;
	float		plane_d;
	float		cylander_d;
	t_vector3	hit_point;

	sphere_d = spheres_while(ray, data);
	plane_d = plane_while(ray, data);
	cylander_d = cyl_while(ray, data);
	if (data->info.save.sphere && sphere_d && (sphere_d < plane_d || !plane_d)
		&& (sphere_d < cylander_d || !cylander_d))
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, sphere_d));
		return (calculate_sphere_lighting(hit_point, data->info.save.sphere, data));
	}
	else if (data->info.save.plane && plane_d && (plane_d < cylander_d || !cylander_d))
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, plane_d));
		return (calculate_plane_lighting(hit_point, data->info.save.plane, data));
	}
	else if (data->info.save.cylinder && cylander_d)
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, cylander_d));
		return (calculate_cylinder_lighting(hit_point, data->info.save.cylinder, data));
	}
	return (0);
}

float	ray_sphere_intersect(t_ray ray, t_sphere *sphere)
{
	t_vector3 oc;
	t_vector3 equa;
	double discriminant;
	float t0;
	float t1;
	
	oc = vector_subtract(ray.origin, sphere->center);
	equa.x = vector_dot(ray.direction, ray.direction);
	equa.y = 2.0 * vector_dot(oc, ray.direction);
	equa.z = vector_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = equa.y * equa.y - 4 * equa.x * equa.z;
	if (discriminant >= 0.0)
		return ((-equa.y - sqrt(discriminant)) / (2.0f * equa.x));
	return (0.0f);
}