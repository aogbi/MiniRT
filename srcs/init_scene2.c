/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:49:15 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:50:06 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_helper(t_scenes *scenes)
{
	t_plane		*plane_tmp;
	t_cylinder	*cylinder_tmp;

	while (scenes->cylinder)
	{
		cylinder_tmp = scenes->cylinder;
		scenes->cylinder = scenes->cylinder->next;
		free(cylinder_tmp);
	}
	while (scenes->plane)
	{
		plane_tmp = scenes->plane;
		scenes->plane = scenes->plane->next;
		free(plane_tmp);
	}
}

void	free_scenes(t_scenes *scenes)
{
	t_sphere	*sphere_tmp;

	if (scenes->camera)
		free(scenes->camera);
	if (scenes->light)
		free(scenes->light);
	if (scenes->ambient)
		free(scenes->ambient);
	while (scenes->sphere)
	{
		sphere_tmp = scenes->sphere;
		scenes->sphere = scenes->sphere->next;
		free(sphere_tmp);
	}
	free_helper(scenes);
	free(scenes);
}

int	init_ambient(char **array, t_scenes *scenes)
{
	t_ambient_lightning	*ambient;

	if (scenes->ambient || count_str_array(array) != 3)
		return (0);
	ambient = malloc(sizeof(t_ambient_lightning));
	if (!ambient)
		return (0);
	else if (!ft_isfloat(array[1]))
		return (free(ambient), ft_str_array_free(array), 0);
	ambient->ratio = ft_atod(array[1]);
	if (ambient->ratio < 0.0 || ambient->ratio > 1.0)
		return (free(ambient), 0);
	ambient->rgb = colors_range(array[2]);
	if (ambient->rgb == -1)
		return (free(ambient), ft_str_array_free(array), 0);
	scenes->ambient = ambient;
	ft_str_array_free(array);
	return (1);
}

int	init_camera(char **array, t_scenes *scenes)
{
	t_camera	*camera;
	int			flag;

	if (scenes->camera || count_str_array(array) != 4)
		return (0);
	else if (!ft_isnum(array[3]))
		return (ft_str_array_free(array), 0);
	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (0);
	flag = 1;
	camera->position = coordinates(ft_split(array[1], ','), &flag);
	camera->direction = coordinates(ft_split(array[2], ','), &flag);
	camera->fov = ft_atoi(array[3]);
	if (!flag || camera->fov < 0 || camera->fov > 180)
		return (ft_str_array_free(array), free(camera), 0);
	scenes->camera = camera;
	ft_str_array_free(array);
	return (1);
}

int	init_light(char **array, t_scenes *scenes)
{
	t_light	*light;
	int		flag;

	if (scenes->light || count_str_array(array) != 4)
		return (0);
	light = malloc(sizeof(t_light));
	if (!light)
		return (0);
	flag = 1;
	light->position = coordinates(ft_split(array[1], ','), &flag);
	light->brightness_ratio = ft_atod(array[2]);
	light->rgb = colors_range(array[3]);
	if (!flag || !ft_isfloat(array[2]) || light->brightness_ratio < 0.00
		|| light->brightness_ratio > 1.00 || light->rgb == -1)
		return (ft_str_array_free(array), free(light), 0);
	scenes->light = light;
	ft_str_array_free(array);
	return (1);
}
