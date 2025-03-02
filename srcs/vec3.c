/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:58:38 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:26:26 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	spheres_while(t_ray ray, t_data *data)
{
	float		tmp;
	t_sphere	*sphere;
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
	float	tmp;
	t_plane	*plane;
	float	t;

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

int	close_intersect_norm(t_data *data, t_ray ray, float plane_d,
	float cylander_d)
{
	t_vector3	hit_point;

	if (data->info.save.plane && plane_d && (plane_d < cylander_d
			|| !cylander_d))
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, plane_d));
		return (calculate_plane_lighting(hit_point, data->info.save.plane,
				data));
	}
	else if (data->info.save.cylinder && cylander_d)
	{
		hit_point = vector_add(ray.origin, scale(ray.direction, cylander_d));
		return (calculate_cylinder_lighting(hit_point, data->info.save.cylinder,
				data));
	}
	return (0);
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
		return (calculate_sphere_lighting(hit_point, data->info.save.sphere,
				data));
	}
	return (close_intersect_norm(data, ray, plane_d, cylander_d));
}
