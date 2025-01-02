/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:14 by aogbi             #+#    #+#             */
/*   Updated: 2025/01/02 02:55:33 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	ray_cylinder_intersect(t_ray ray, t_cylinder cylinder)
{
}

t_img	*calculate_ray_directions(t_scenes *scenes)
{
	;
}

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

int	main(int argc, char **argv)
{
	t_data data;
	t_scenes *scenes;

	if (argc != 2)
		return (write(2, "usage: ./miniRT [file.rt]\n", 26), 1);
	else if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])))
		return (write(2, "file must be a .rt file\n", 24), 1);
	scenes = scene_description(argv[1]);
	if (!scenes)
		return (write (2, "Error\n", 7), 1);
	calculate_ray_directions(scenes);
	// data.mlx_ptr = mlx_init();
	// data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "MiniRT");
	// data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	// data.img.width = WIDTH;
	// data.img.height = HEIGHT;
	// data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
	// 		&data.img.line_len, &data.img.endian);
	// mlx_key_hook(data.win_ptr, key_hook, &data);
	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	// mlx_loop(data.mlx_ptr);
	return (0);
}