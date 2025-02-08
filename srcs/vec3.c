/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:58:38 by aogbi             #+#    #+#             */
/*   Updated: 2025/02/08 18:31:35 by aogbi            ###   ########.fr       */
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

int	calculate_sphere_lighting(t_vector3 point, t_vector3 normal,
		t_sphere *sphere, t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	double		intensity;

	light_direction = vector_normalize(vector_subtract(point,
				data->info.scenes->light->position));
	intensity = fmax(0.0, -vector_dot(normal, light_direction))
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

int	calculate_plane_lighting(t_vector3 point, t_vector3 normal, t_plane *plane,
		t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	double		intensity;

	light_direction = vector_normalize(vector_subtract(data->info.scenes->light->position,
				point));
	intensity = fmax(0.0, vector_dot(normal, light_direction))
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

double	intersect_cylinder(t_ray ray, t_cylinder *cyl)
{
	t_vector3	oc;
	t_vector3	d_cross_v;
	t_vector3	oc_cross_v;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		delta;
	double		t1;
	double		t2;
	double		t;
	double		h1;
	double		h2;

	oc = vector_subtract(ray.origin, cyl->center);
	d_cross_v = vector_cross(ray.direction, cyl->axis);
	oc_cross_v = vector_cross(oc, cyl->axis);
	a = vector_dot(d_cross_v, d_cross_v);
	b = 2 * vector_dot(oc_cross_v, d_cross_v);
	c = vector_dot(oc_cross_v, oc_cross_v) - (cyl->radias * cyl->radias);
	discriminant = (b * b) - (4 * a * c);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	t1 = (-b - sqrt(delta)) / (2 * a);
	t2 = (-b + sqrt(delta)) / (2 * a);
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

float	spheres_while(t_ray ray, t_sphere **sphere)
{
	float		tmp;
	t_sphere	*tmp_sphere;
	float		t;

	tmp_sphere = NULL;
	t = 0;
	if (*sphere)
	{
		t = fmax(0.0f, ray_sphere_intersect(ray, *sphere));
		tmp_sphere = *sphere;
		*sphere = (*sphere)->next;
	}
	while (*sphere)
	{
		tmp = fmax(0.0f, ray_sphere_intersect(ray, *sphere));
		if (tmp > 0.0f && (t == 0.0f || tmp < t))
		{
			t = tmp;
			tmp_sphere = *sphere;
		}
		*sphere = (*sphere)->next;
	}
	*sphere = tmp_sphere;
	return (t);
}

float	plane_while(t_ray ray, t_plane **plane)
{
	float		tmp;
	t_sphere	*tmp_sphere;
	float		t;

	tmp_sphere = NULL;
	t = 0;
	if (*plane)
	{
		t = fmax(0.0f, ray_plane_intersect(ray, **plane));
		tmp_sphere = *plane;
		*plane = (*plane)->next;
	}
	while (*plane)
	{
		tmp = fmax(0.0f, ray_plane_intersect(ray, **plane));
		if (tmp > 0.0f && (t == 0.0f || tmp < t))
		{
			t = tmp;
			tmp_sphere = *plane;
		}
		*plane = (*plane)->next;
	}
	*plane = tmp_sphere;
	return (t);
}

float	cyl_while(t_ray ray, t_cylinder **cyl)
{
	float		tmp;
	t_sphere	*tmp_sphere;
	float		t;

	tmp_sphere = NULL;
	t = 0;
	if (*cyl)
	{
		t = fmax(0.0f, intersect_cylinder(ray, *cyl));
		tmp_sphere = *cyl;
		*cyl = (*cyl)->next;
	}
	while (*cyl)
	{
		tmp = fmax(0.0f, intersect_cylinder(ray, *cyl));
		if (tmp > 0.0f && (t == 0.0f || tmp < t))
		{
			t = tmp;
			tmp_sphere = *cyl;
		}
		*cyl = (*cyl)->next;
	}
	*cyl = tmp_sphere;
	return (t);
}

int	close_intersect(t_data *data, t_ray ray)
{
	int			colore;
	t_sphere	**sphere;
	t_plane		**plane;
	t_cylinder	**cyl;
	t_vector3	normal;
	float		sphere_d;
	float		plane_d;
	float		cylander_d;
	t_vector3	hit_point;

	colore = 0;
	sphere = malloc(sizeof(t_sphere *));
	*sphere = data->info.scenes->sphere;
	sphere_d = spheres_while(ray, sphere);
	plane = malloc(sizeof(t_plane *));
	*plane = data->info.scenes->plane;
	plane_d = plane_while(ray, plane);
	cyl = malloc(sizeof(t_cylinder *));
	*cyl = data->info.scenes->cylinder;
	cylander_d = cyl_while(ray, cyl);
	if (*sphere && sphere_d && (sphere_d < plane_d || !plane_d)
		&& (sphere_d < cylander_d || !cylander_d))
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, sphere_d));
		normal = vector_normalize(vector_subtract(hit_point,
					(*sphere)->center));
		colore = calculate_sphere_lighting(hit_point, normal, *sphere, data);
	}
	else if (*plane && plane_d && (plane_d < cylander_d || !cylander_d))
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, plane_d));
		normal = (*plane)->direction;
		colore = calculate_plane_lighting(hit_point, normal, *plane, data);
	}
	else if (*cyl && cylander_d)
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, cylander_d));
		colore = calculate_cylinder_lighting(hit_point, *cyl, data);
	}
	free(plane);
	free(cyl);
	free(sphere);
	return (colore);
}

float	ray_sphere_intersect(t_ray ray, t_sphere *sphere)
{
	t_vector3 oc;
	double a;
	double b;
	double c;
	double discriminant;
	float t0;
	float t1;

	oc = vector_subtract(ray.origin, sphere->center);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(oc, ray.direction);
	c = vector_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0.0)
		return ((-b - sqrt(discriminant)) / (2.0f * a));
	return (0.0);
}