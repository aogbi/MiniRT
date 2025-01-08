/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:14 by aogbi             #+#    #+#             */
/*   Updated: 2025/01/08 15:19:23 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	key_hook(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = NULL;
		mlx_loop_end(data->mlx_ptr);
	}
}

void	init_data(t_data *data)
{
	data->info.aspect_ratio = 16.0 / 9.0;
	data->img.width = WIDTH; /*variable*/
	data->img.height = (int)(data->img.width / data->info.aspect_ratio);
	if (data->img.height < 1)
		data->img.height = 1;
	data->info.focal_length = 1.0;
	data->info.viewport_height = 2.0;
	data->info.viewport_width = data->info.viewport_height
		* (double)data->img.width / data->img.height;
	data->info.viewport_u = (t_vector3){data->info.viewport_width, 0, 0};
	data->info.viewport_v = (t_vector3){0, -data->info.viewport_height, 0};
	data->info.pixel_delta_u = scale(data->info.viewport_u, 1.0
			/ data->img.width);
	data->info.pixel_delta_v = scale(data->info.viewport_v, 1.0
			/ data->img.height);
	data->info.viewport_upper_left = vector_subtract(vector_subtract(vector_subtract(data->info.scenes->camera->position,
					(t_vector3){0, 0, data->info.focal_length}),
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

int	calculate_lighting(t_vector3 point, t_vector3 normal, t_data *data)
{
	int			r;
	int			g;
	int			b;
	t_vector3	light_direction;
	double		intensity;

	light_direction = vector_normalize(vector_subtract(data->info.scenes->light->position,
				point));
	intensity = vector_dot(normal, scale(light_direction, -1));
	r = (int)(((data->info.scenes->sphere->rgb >> 16) & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* (((data->info.scenes->light->rgb >> 16) & 0xFF) / 255.0));
	g = (int)(((data->info.scenes->sphere->rgb >> 8) & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* (((data->info.scenes->light->rgb >> 8) & 0xFF) / 255.0));
	b = (int)((data->info.scenes->sphere->rgb & 0xFF) * intensity
			* data->info.scenes->light->brightness_ratio
			* ((data->info.scenes->light->rgb & 0xFF) / 255.0));
	return ((r << 16) | (g << 8) | b);
}

int	render(t_data *data)
{
	int			j;
	int			i;
	t_vector3	pixel_center;
	t_vector3	ray_direction;
	t_ray		ray;
	t_vector3	intersect_point;
	t_vector3	normal;
	int			color;

	j = 0;
	while (j < data->img.height)
	{
		printf("\rScanlines remaining: %d%% ", (j * 100) / data->img.height);
		i = 0;
		while (i < data->img.width)
		{
			pixel_center = vector_add(data->info.pixel00_loc,
					vector_add(scale(data->info.pixel_delta_u, i),
						scale(data->info.pixel_delta_v, j)));
			ray_direction = vector_subtract(pixel_center,
					data->info.scenes->camera->position);
			ray = (t_ray){data->info.scenes->camera->position, ray_direction};
			// calculate the color of the pixel at (i, j) in the image
			// put the color of the pixel at (i, j) in the image
			intersect_point = ray_sphere_intersect(ray,
					data->info.scenes->sphere);
			if (!vector3_equal(intersect_point, (t_vector3){0, 0, 0}))
			{
				normal = vector_normalize(vector_subtract(intersect_point,
							data->info.scenes->sphere->center));
				color = calculate_lighting(intersect_point, normal, data);
				put_color_to_pixel(data, i, j, color);
			}
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
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.img.width, data.img.height,
			"MiniRT");
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	mlx_loop(data.mlx_ptr);
	free_scenes(data.info.scenes);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
