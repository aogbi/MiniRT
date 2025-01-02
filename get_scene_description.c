/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_description.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:34:54 by aogbi             #+#    #+#             */
/*   Updated: 2025/01/02 01:26:48 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

int ft_isnum(char *str)
{
	if (!str)
		return (0);
	else if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int ft_isfloat(char *str)
{
	int	flag;

	if (!str)
		return (0);
	else if (*str == '-' || *str == '+')
		str++;
	flag = 0;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '.')
			return (0);
		else if (*str == '.')
		{
			if (flag)
				return (0);
			flag = 1;
		}
		str++;
	}
	return (1);
}

void ft_str_array_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int count_str_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

t_vector3 coordinates(char **array, int *flag)
{
	t_vector3	vector;
	int			i;

	i = 0;
	while(i)
	{
		if (!ft_isfloat(array[i]) || i > 2)
		{
			*flag = 0;
			break;
		}
		else if(i == 0)
			vector.x = ft_atod(array[0]);
		else if(i == 1)
			vector.y = ft_atod(array[1]);
		else if(i == 2)
			vector.z = ft_atod(array[2]);
		i++;
	}
	ft_str_array_free(array);
	return (vector);
}

int colors_range(char *str)
{
	char	**array;
	int		i;
	int 	color;

	array = ft_split(str, ',');
	i = 0;
	color = 0;
	while (array[i])
	{
		if (!ft_isnum(array[i]) || ft_atoi(array[i]) < 0 || ft_atoi(array[i]) > 255)
			return (ft_str_array_free(array), -1);
		color = (color << 8) | ft_atoi(array[i]);
		i++;
	}
	ft_str_array_free(array);
	if (i != 3)
		return (-1);
	return (color);
}

int init_ambient(char **array, t_scenes *scenes)
{
	t_ambient_lightning	*ambient;

	if (count_str_array(array) != 3)
		return (0);
	ambient = malloc(sizeof(t_ambient_lightning));
	if (!ambient)
		return (0);
	else if (!ft_isfloat(array[1]))
		return (free(ambient), ft_str_array_free(array), 0);
	ambient->ratio = ft_atod(array[1]);
	if (ambient->ratio < 0 || ambient->ratio > 1)
		return (free(ambient), 0);
	ambient->rgb = colors_range(array[2]);
	if (ambient->rgb == -1)
		return (free(ambient), ft_str_array_free(array), 0);
	scenes->ambient = ambient;
	ft_str_array_free(array);
	return (1);
}

int init_camera(char **array, t_scenes *scenes)
{
	t_camera	*camera;
	int			flag;

	if (count_str_array(array) != 4)
		return (0);
	else if (!ft_isint(array[3]))
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

int init_light(char **array, t_scenes *scenes)
{
	// t_light *light;

	// if (count_str_array(array) != 3)
	// 	return (0);
	// light = malloc(sizeof(t_light));
	// if (!light)
	// 	return (0);
	// light->position = coordinates(ft_split(array[1], ','));
	// if (!ft_isfloat(array[2]) || ft_atod(array[2]) < 0 || ft_atod(array[2]) > 1)
	// 	return (free(light), 0);
	// light->brightness_ratio = ft_atod(array[2]);
	// scenes->light = light;
	return (1);
}

int init_sphere(char **array, t_scenes *scenes)
{
	// t_sphere *sphere;

	// if (count_str_array(array) != 3)
	// 	return (0);

	// sphere = malloc(sizeof(t_sphere));
	// if (!sphere)
	// 	return (0);
	// sphere->center = coordinates(ft_split(array[1], ','));
	// if (!ft_isfloat(array[2]) || ft_atod(array[2]) <= 0)
	// 	return (free(sphere), 0);
	// sphere->radius = ft_atod(array[2]) / 2;
	// sphere->rgb = colors_range(array[3]);
	// scenes->sphere = sphere;
	return (1);
}

int init_plane(char **array, t_scenes *scenes)
{
	// t_plane *plane;

	// if (count_str_array(array) != 3)
	// 	return (0);
	// plane = malloc(sizeof(t_plane));
	// if (!plane)
	// 	return (0);
	// plane->position = coordinates(ft_split(array[1], ','));
	// plane->direction = coordinates(ft_split(array[2], ','));
	// if (plane->direction.x == 0 && plane->direction.y == 0 && plane->direction.z == 0)
	// 	return (free(plane), 0);
	// plane->rgb = colors_range(array[3]);
	// scenes->plane = plane;
	return (1);
}

int init_cylinder(char **array, t_scenes *scenes)
{
	// t_cylinder *cylinder;

	// if (ft_split_count(array) != 6)
	// 	return (0);
	// cylinder = malloc(sizeof(t_cylinder));
	// if (!cylinder)
	// 	return (0);
	// cylinder->center = coordinates(ft_split(array[1], ','));
	// cylinder->orientation = coordinates(ft_split(array[2], ','));
	// if (!ft_isfloat(array[3]) || ft_atod(array[3]) <= 0 ||
	// 	!ft_isfloat(array[4]) || ft_atod(array[4]) <= 0)
	// 	return (free(cylinder), 0);
	// cylinder->diameter = ft_atod(array[3]);
	// cylinder->height = ft_atod(array[4]);
	// cylinder->rgb = colors_range(array[5]);
	// scenes->cylinder = cylinder;
	return (1);
}

int description_line(t_scenes *scenes, char *line)
{
	char	**array;

	array = ft_split(line, ' ');
	if (!array)
		return (0);
	if (!ft_strcmp(array[0], "A"))
		return (init_ambient(array, scenes));
	else if (!ft_strcmp(array[0], "C"))
		return (init_camera(array, scenes));
	else if (!ft_strcmp(array[0], "L"))
		return (init_light(array, scenes));
	else if (!ft_strcmp(array[0], "sp"))
		return (init_sphere(array, scenes));
	else if (!ft_strcmp(array[0], "pl"))
		return (init_plane(array, scenes));
	else if (!ft_strcmp(array[0], "cy"))
		return (init_cylinder(array, scenes));
	else
		return (ft_str_array_free(array), 0);
}

int init_scenes(t_scenes *scenes)
{
	scenes->camera = NULL;
	scenes->light = NULL;
	scenes->ambient = NULL;
	scenes->sphere = NULL;
	scenes->cylinder = NULL;
	scenes->plane = NULL;
	return (0);
}

t_scenes *scene_description(char *file_name)
{
	t_scenes *scenes;
	char *line;
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (write(2, "file not found\n", 16), NULL);
	scenes = malloc(sizeof(t_scenes));
	if (!scenes || init_scenes(scenes))
		return (write(2, "malloc failed\n", 15), NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!description_line(scenes, line))
			return (free(scenes), NULL);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (scenes);
}


// int ft_isnum(char *str)
// {
// 	if (!str)
// 		return (0);
// 	else if (*str == '-' || *str == '+')
// 		str++;
// 	while (*str)
// 	{
// 		if (!ft_isdigit(*str))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

// int ft_isfloat(char *str)
// {
// 	int	flag;

// 	if (!str)
// 		return (0);
// 	else if (*str == '-' || *str == '+')
// 		str++;
// 	flag = 0;
// 	while (*str)
// 	{
// 		if (!ft_isdigit(*str) && *str != '.')
// 			return (0);
// 		else if (*str == '.')
// 		{
// 			if (flag)
// 				return (0);
// 			flag = 1;
// 		}
// 		str++;
// 	}
// 	return (1);
// }

// void ft_str_array_free(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i])
// 		free(array[i++]);
// 	free(array);
// }

// t_vector3	coordinates(char **array)
// {
// 	t_vector3	vector;

// 	vector.x = ft_atod(array[0]);
// 	vector.y = ft_atod(array[1]);
// 	vector.z = ft_atod(array[2]);
// 	ft_str_array_free(array);
// 	return (vector);
// }

// int	colors_range(char *str)
// {
// 	char	**array;
// 	int		i;
// 	int 	color;

// 	array = ft_split(str, ',');
// 	i = 0;
// 	color = 0;
// 	while (array[i])
// 	{
// 		if (!ft_isnum(array[i]))
// 			return (ft_str_array_free(array), -1);
// 		color = (color + (255 * i)) + ft_atoi(array[i]);
// 		i++;
// 	}
// 	ft_str_array_free(array);
// 	if(i != 3)
// 		return (-1);
// 	return (color);
// }

// int	init_ambient(char **array, t_scenes *scenes)
// {
// 	t_ambient_lightning	ambient;
// 	int					i;

// 	i = 1;
// 	while(array[i])
// 	{
// 		if (i == 1)
// 			ambient.ratio = ft_atod(array[i]);
// 		else if (i == 2)
// 			;
// 		else
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	init_camera(char **array, t_scenes *scenes)
// {
// }

// int	init_light(char **array, t_scenes *scenes)
// {
// }

// int	init_sphere(char **array, t_scenes *scenes)
// {
// }

// int	init_plane(char **array, t_scenes *scenes)
// {
// }

// int	init_cylinder(char **array, t_scenes *scenes)
// {
// }

// int	description_line(t_scenes *scenes, char *line)
// {
// 	char	**array;

// 	array = ft_split(line, ' ');
// 	free(line);
// 	if (!array)
// 		return (0);
// 	else if (ft_strcmp(array[0], "A"))
// 		return (init_ambient(array, scenes));
// 	else if (ft_strcmp(array[0], "C"))
// 		return (init_camera(array, scenes));
// 	else if (ft_strcmp(array[0], "L"))
// 		return (init_light(array, scenes));
// 	else if (ft_strcmp(array[0], "sp"))
// 		return (init_sphere(array, scenes));
// 	else if (ft_strcmp(array[0], "pl"))
// 		return (init_plane(array, scenes));
// 	else if (ft_strcmp(array[0], "cl"))
// 		return (init_cylinder(array, scenes));
// 	else
// 		return (0);
// }

// int	init_scenes(t_scenes *scenes)
// {
// 	scenes->camera = NULL;
// 	scenes->light = NULL;
// 	scenes->ambient = NULL;
// 	scenes->sphere = NULL;
// 	scenes->cylinder = NULL;
// 	scenes->plane = NULL;
// 	return (0);
// }

// t_scenes	*scene_description(char *file_name)
// {
// 	t_scenes	*scenes;
// 	char		*line;
// 	int			fd;

// 	fd = open(file_name, O_RDONLY);
// 	if (fd < 0)
// 		return (write(2, "file not found\n", 16), NULL);
// 	scenes = malloc(sizeof(t_scenes));
// 	if (!scenes || init_scenes(scenes))
// 		return (write(2, "malloc failed\n", 15), NULL);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (!description_line(scenes, line))
// 			return (free(scenes), NULL);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (scenes);
// }
