/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:14 by aogbi             #+#    #+#             */
/*   Updated: 2024/10/25 14:00:44 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void calculate_ray_directions(t_data *data)
{
    Camera camera = {vector_create(-1.0, 0.0, 0.0),(Vector3){0, 0, -1}, M_PI / 2.0, 16.0 / 9.0};
    float viewport_height = 2.0 * tan(camera.fov / 2.0);
    float viewport_width = viewport_height * camera.aspect_ratio;
    Sphere sphere = {vector_create(0.0, 0.0, -5.0), 1.0};
    for (int j = 0; j < data->img.height; j++) {
        for (int i = 0; i < data->img.width; i++) {
            float u = (i + 0.5) / (float)data->img.width;
            float v = (j + 0.5) / (float)data->img.height;
            Vector3 pixel_position = {
                u * viewport_width - viewport_width / 2.0,
                v * viewport_height - viewport_height / 2.0,
                -1.0
            };
            Vector3 ray_direction = vector_normalize(vector_subtract(pixel_position, camera.position));
            Ray ray = {camera.position, ray_direction};
            double t = ray_sphere_intersect(ray, sphere);
            if (t > 0) {
                Vector3 intersection_point = vector_create(
                    ray.origin.x + t * ray.direction.x,
                    ray.origin.y + t * ray.direction.y,
                    ray.origin.z + t * ray.direction.z
                );
                Vector3 normal = vector_normalize(vector_subtract(intersection_point, sphere.center));
                double intensity = calculate_lighting(intersection_point, normal);
                unsigned int *img_addr = (unsigned int *)data->img.addr;
                img_addr[i + (j * WIDTH)] = 0xFF0000;
            }
        }
    }
}


int main()
{
    t_data data;
	data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "MiniRT");
    data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
    data.img.width = WIDTH;
    data.img.height = HEIGHT;
    data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
    calculate_ray_directions(&data);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
    mlx_loop(data.mlx_ptr);
    return (0);
}