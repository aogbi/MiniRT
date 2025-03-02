/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:24:37 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:34:23 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	calculate_sphere_lighting(t_vector3 point, t_sphere *sphere, t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	float		intensity;

	light_direction = vector_subtract(data->info.scenes->light->position,
			point);
	intensity = 0.0f;
	if (shadow(data, point, &light_direction))
		intensity = fmax(0.0, vector_dot(vector_normalize(vector_subtract(point,
							sphere->center)), light_direction))
			* data->info.scenes->light->brightness_ratio;
	intensity += data->info.scenes->ambient->ratio;
	intensity = fmin(1.0, intensity);
	r = (int)(((float)((sphere->rgb >> 16) & 0xFF)) * intensity);
	g = (int)(((float)((sphere->rgb >> 8) & 0xFF)) * intensity);
	b = (int)(((float)((sphere->rgb) & 0xFF)) * intensity);
	r *= (int)((float)((((data->info.scenes->ambient->rgb >> 16) & 0xFF) / 255)
				* (((data->info.scenes->light->rgb >> 16) & 0xFF) / 255)));
	g *= (int)((float)((((data->info.scenes->ambient->rgb >> 8) & 0xFF) / 255)
				* (((data->info.scenes->light->rgb >> 8) & 0xFF) / 255)));
	b *= (int)((float)(((data->info.scenes->ambient->rgb & 0xFF) / 255)
				* ((data->info.scenes->light->rgb & 0xFF) / 255)));
	return ((r << 16) | (g << 8) | b);
}

int	calculate_plane_lighting(t_vector3 point, t_plane *plane, t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	float		intensity;

	light_direction = vector_subtract(data->info.scenes->light->position,
			point);
	intensity = 0.0f;
	if (shadow(data, point, &light_direction))
		intensity = fmax(0.0, vector_dot(plane->direction, light_direction))
			* data->info.scenes->light->brightness_ratio;
	intensity += data->info.scenes->ambient->ratio;
	intensity = fmin(1.0, intensity);
	r = (int)(((float)((plane->rgb >> 16) & 0xFF)) * intensity);
	g = (int)(((float)((plane->rgb >> 8) & 0xFF)) * intensity);
	b = (int)(((float)((plane->rgb) & 0xFF)) * intensity);
	r *= (int)((float)((((data->info.scenes->ambient->rgb >> 16) & 0xFF) / 255)
				* (((data->info.scenes->light->rgb >> 16) & 0xFF) / 255)));
	g *= (int)((float)((((data->info.scenes->ambient->rgb >> 8) & 0xFF) / 255)
				* (((data->info.scenes->light->rgb >> 8) & 0xFF) / 255)));
	b *= (int)((float)(((data->info.scenes->ambient->rgb & 0xFF) / 255)
				* ((data->info.scenes->light->rgb & 0xFF) / 255)));
	return ((r << 16) | (g << 8) | b);
}

int	calculate_colore(t_cylinder *cyl, float intensity)
{
	int			r;
	int			g;
	int			b;

	r = fmin(255, fmax(0, (int)(((float)((cyl->rgb >> 16) & 0xFF))
					* intensity)));
	g = fmin(255, fmax(0, (int)(((float)((cyl->rgb >> 8) & 0xFF))
					* intensity)));
	b = fmin(255, fmax(0, (int)(((float)(cyl->rgb & 0xFF)) * intensity)));
	return ((r << 16) | (g << 8) | b);
}

int	calculate_cylinder_lighting(t_vector3 point, t_cylinder *cyl, t_data *data)
{
	t_vector3	proj;
	t_vector3	normal;
	t_vector3	light_dir;
	float		intensity;

	proj = vector_add(cyl->center, scale(cyl->axis,
				vector_dot(vector_subtract(point, cyl->center), cyl->axis)));
	normal = vector_normalize(vector_subtract(point, proj));
	light_dir = vector_subtract(data->info.scenes->light->position, point);
	intensity = 0.0f;
	if (shadow(data, point, &light_dir))
		intensity = fmax(0.0, vector_dot(normal, light_dir))
			* data->info.scenes->light->brightness_ratio;
	intensity += data->info.scenes->ambient->ratio;
	intensity = fmin(1.0, intensity);
	return (calculate_colore(cyl, intensity));
}
