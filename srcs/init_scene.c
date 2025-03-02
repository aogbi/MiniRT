/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:44:35 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:50:20 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	init_sphere(char **array, t_scenes *scenes)
{
	t_sphere	*sphere;
	int			flag;

	if (count_str_array(array) != 4)
		return (0);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	flag = 1;
	sphere->center = coordinates(ft_split(array[1], ','), &flag);
	sphere->radius = ft_atod(array[2]) / 2.0f;
	sphere->rgb = colors_range(array[3]);
	sphere->next = NULL;
	if (!flag || !ft_isfloat(array[2]) || sphere->radius <= 0.0f
		|| sphere->rgb == -1)
		return (ft_str_array_free(array), free(sphere), 0);
	else if (!scenes->sphere)
		scenes->sphere = sphere;
	else
	{
		sphere->next = scenes->sphere;
		scenes->sphere = sphere;
	}
	ft_str_array_free(array);
	return (1);
}

void	init_plane_norm(t_plane *plane, char **array, int flag)
{
	plane->position = coordinates(ft_split(array[1], ','), &flag);
	plane->direction = coordinates(ft_split(array[2], ','), &flag);
	plane->rgb = colors_range(array[3]);
	plane->next = NULL;
}

int	init_plane(char **array, t_scenes *scenes)
{
	t_plane	*plane;
	int		flag;

	if (count_str_array(array) != 4)
		return (0);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	flag = 1;
	init_plane_norm(plane, array, flag);
	if (!flag || plane->direction.x < -1.0 || plane->direction.x > 1.0
		|| plane->direction.y < -1.0 || plane->direction.y > 1.0
		|| plane->direction.z < -1.0 || plane->direction.z > 1.0
		|| plane->rgb == -1)
		return (ft_str_array_free(array), free(plane), 0);
	else if (!scenes->plane)
		scenes->plane = plane;
	else
	{
		plane->next = scenes->plane;
		scenes->plane = plane;
	}
	ft_str_array_free(array);
	return (1);
}

void	init_cyl_norm(t_cylinder *cylinder, char **array, int *flag)
{
	*flag = 1;
	cylinder->center = coordinates(ft_split(array[1], ','), flag);
	cylinder->axis = coordinates(ft_split(array[2], ','), flag);
	cylinder->radias = ft_atod(array[3]) / 2.0;
	cylinder->height = ft_atod(array[4]);
	cylinder->rgb = colors_range(array[5]);
	cylinder->next = NULL;
}

int	init_cylinder(char **array, t_scenes *scenes)
{
	t_cylinder	*cylinder;
	int			flag;

	if (count_str_array(array) != 6)
		return (0);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	init_cyl_norm(cylinder, array, &flag);
	if (!flag || !ft_isfloat(array[3]) || cylinder->radias <= 0
		|| cylinder->axis.x < -1.0 || cylinder->axis.x > 1.0
		|| cylinder->axis.y < -1.0 || cylinder->axis.y > 1.0
		|| cylinder->axis.z < -1.0 || cylinder->axis.z > 1.0
		|| !ft_isfloat(array[4]) || cylinder->height <= 0 || cylinder->rgb
		== -1)
		return (ft_str_array_free(array), free(cylinder), 0);
	else if (!scenes->cylinder)
		scenes->cylinder = cylinder;
	else
	{
		cylinder->next = scenes->cylinder;
		scenes->cylinder = cylinder;
	}
	ft_str_array_free(array);
	return (1);
}
