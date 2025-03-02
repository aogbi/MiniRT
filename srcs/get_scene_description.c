/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_description.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:34:54 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:50:53 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3	coordinates(char **array, int *flag)
{
	t_vector3	vector;
	int			i;

	i = 0;
	while (array[i])
	{
		if (!ft_isfloat(array[i]) || i > 2)
		{
			*flag = 0;
			break ;
		}
		else if (i == 0)
			vector.x = ft_atod(array[0]);
		else if (i == 1)
			vector.y = ft_atod(array[1]);
		else if (i == 2)
			vector.z = ft_atod(array[2]);
		i++;
	}
	if (i != 3)
		*flag = 0;
	ft_str_array_free(array);
	return (vector);
}

int	colors_range(char *str)
{
	char	**array;
	int		i;
	int		color;

	array = ft_split(str, ',');
	i = 0;
	color = 0;
	while (array[i])
	{
		if (!ft_isnum(array[i]) || ft_atoi(array[i]) < 0
			|| ft_atoi(array[i]) > 255)
			return (ft_str_array_free(array), -1);
		color = (color << 8) | ft_atoi(array[i]);
		i++;
	}
	ft_str_array_free(array);
	if (i != 3 || color < 0 || color > 0xFFFFFF)
		return (-1);
	return (color);
}

int	description_line(t_scenes *scenes, char *line)
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

int	init_scenes(t_scenes *scenes)
{
	scenes->camera = NULL;
	scenes->light = NULL;
	scenes->ambient = NULL;
	scenes->sphere = NULL;
	scenes->cylinder = NULL;
	scenes->plane = NULL;
	return (0);
}

t_scenes	*scene_description(char *file_name)
{
	t_scenes	*scenes;
	char		*line;
	int			fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (write(2, "file not found\n", 16), NULL);
	scenes = malloc(sizeof(t_scenes));
	if (!scenes || init_scenes(scenes))
		return (write(2, "malloc failed\n", 15), NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && !description_line(scenes, line))
			return (free_scenes(scenes), free(line), close(fd), NULL);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (scenes);
}
