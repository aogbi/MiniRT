/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 00:37:51 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 00:40:34 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	move_camera(t_data *data, t_vector3 vect)
{
	data->info.scenes->camera->position
		= vector_add(data->info.scenes->camera->position, vect);
	data->info.viewport_upper_left = vector_subtract(vector_subtract
			(vector_add(data->info.scenes->camera->position,
					data->info.scenes->camera->direction),
				scale(data->info.viewport_u, 0.5)), scale(data->info.viewport_v,
				0.5));
	data->info.pixel00_loc = vector_add(data->info.viewport_upper_left,
			scale(vector_add(data->info.pixel_delta_u,
					data->info.pixel_delta_v), 0.5));
	render(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0,
		0);
}

int	x_button_in_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = NULL;
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	key_hook(int key, t_data *data)
{
	if (key == XK_Escape)
		x_button_in_window(data);
	else if (key == 'd')
		move_camera(data, (t_vector3){1, 0, 0});
	else if (key == 'a')
		move_camera(data, (t_vector3){-1, 0, 0});
	else if (key == 'w')
		move_camera(data, (t_vector3){0, 1, 0});
	else if (key == 's')
		move_camera(data, (t_vector3){0, -1, 0});
	else if (key == 65362)
		move_camera(data, (t_vector3){0, 0, 1});
	else if (key == 65364)
		move_camera(data, (t_vector3){0, 0, -1});
	return (1);
}

void	hooks(t_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img.width,
			data->img.height, "MiniRT");
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_hook(data->win_ptr, ClientMessage, 0, &x_button_in_window, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	mlx_loop(data->mlx_ptr);
	free_scenes(data->info.scenes);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}
