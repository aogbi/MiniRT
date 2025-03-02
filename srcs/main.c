/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:14 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:39:38 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_data(t_data *data)
{
	data->info.aspect_ratio = 16.0 / 9.0;
	data->img.width = WIDTH;
	data->img.height = (int)(data->img.width / data->info.aspect_ratio);
	if (data->img.height < 1)
		data->img.height = 1;
	data->info.theta = data->info.scenes->camera->fov * M_PI / 180.0;
	data->info.viewport_height = 2.0 * tan(data->info.theta / 2);
	data->info.viewport_width = data->info.viewport_height
		* (float)data->img.width / data->img.height;
	data->info.viewport_u = (t_vector3){data->info.viewport_width, 0, 0};
	data->info.viewport_v = (t_vector3){0, -data->info.viewport_height, 0};
	data->info.pixel_delta_u = scale(data->info.viewport_u, 1.0
			/ data->img.width);
	data->info.pixel_delta_v = scale(data->info.viewport_v, 1.0
			/ data->img.height);
	data->info.viewport_upper_left = vector_subtract(vector_subtract(
				vector_add(data->info.scenes->camera->position,
					data->info.scenes->camera->direction),
				scale(data->info.viewport_u, 0.5)), scale(data->info.viewport_v,
				0.5));
	data->info.pixel00_loc = vector_add(data->info.viewport_upper_left,
			scale(vector_add(data->info.pixel_delta_u,
					data->info.pixel_delta_v), 0.5));
}

void	put_color_to_pixel(t_data *data, int i, int j, int color)
{
	int	*img_addr;

	img_addr = (int *)data->img.addr;
	img_addr[i + (j * (data->img.width))] = color;
}

t_ray	ray_render(t_data *data, int i, int j)
{
	t_vector3	pixel_center;
	t_vector3	ray_direction;
	t_ray		ray;

	pixel_center = vector_add(data->info.pixel00_loc,
			vector_add(scale(data->info.pixel_delta_u, i),
				scale(data->info.pixel_delta_v, j)));
	ray_direction = vector_subtract(pixel_center,
			data->info.scenes->camera->position);
	ray = (t_ray){data->info.scenes->camera->position, ray_direction};
	return (ray);
}

int	render(t_data *data)
{
	int			j;
	int			i;

	j = 0;
	while (j < data->img.height)
	{
		printf("\rScanlines remaining: %d%% ", (j * 100) / data->img.height);
		i = 0;
		while (i < data->img.width)
		{
			put_color_to_pixel(data, i, j, close_intersect(data,
					ray_render(data, i, j)));
			i++;
		}
		j++;
	}
	printf("\rDone.                                       \n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (write(2, "usage: ./miniRT [file.rt]\n", 26), 1);
	else if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])))
		return (write(2, "file must be a .rt file\n", 24), 1);
	data.info.scenes = scene_description(argv[1]);
	if (!data.info.scenes || !data.info.scenes->camera
		|| !data.info.scenes->ambient || !data.info.scenes->light)
		return (write(2, "Error\n", 7), 1);
	init_data(&data);
	data.mlx_ptr = mlx_init();
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.img.width,
			data.img.height);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	render(&data);
	hooks(&data);
	return (0);
}
