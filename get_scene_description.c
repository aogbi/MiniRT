/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_description.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:34:54 by aogbi             #+#    #+#             */
/*   Updated: 2024/12/16 19:07:09 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

int	init_ambient(char **array, t_scenes *scenes)
{
	t_ambient_lightning	ambient;
	int					i;

	i = 1;
	while(array[i])
	{
		if (i == 1)
		;
		else if (i == 2)
		;
			return (0);
		i++;
	}
	return (1);
}

int	init_camera(char **array, t_scenes *scenes)
{
}

int	init_light(char **array, t_scenes *scenes)
{
}

int	init_sphere(char **array, t_scenes *scenes)
{
}

int	init_plane(char **array, t_scenes *scenes)
{
}

int	init_cylinder(char **array, t_scenes *scenes)
{
}

int	description_line(t_scenes *scenes, char *line)
{
	char	**array;

	array = ft_split(line, ' ');
	free(line);
	if (!array)
		return (0);
	else if (ft_strcmp(array[0], "A"))
		return (init_ambient(array, scenes));
	else if (ft_strcmp(array[0], "C"))
		return (init_camera(array, scenes));
	else if (ft_strcmp(array[0], "L"))
		return (init_light(array, scenes));
	else if (ft_strcmp(array[0], "sp"))
		return (init_sphere(array, scenes));
	else if (ft_strcmp(array[0], "pl"))
		return (init_plane(array, scenes));
	else if (ft_strcmp(array[0], "cl"))
		return (init_cylinder(array, scenes));
	else
		return (0);
}

int	init_scenes(t_scenes *scenes)
{
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
		if (!description_line(scenes, line))
			return (free(scenes), NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (scenes);
}
