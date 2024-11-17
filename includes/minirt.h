/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:26 by aogbi             #+#    #+#             */
/*   Updated: 2024/10/25 14:11:10 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include "../Libft/libft.h"
#include <mlx.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600

typedef struct {
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
    int        width;
    int        height;
}	t_img;

typedef struct {
    void	*mlx_ptr;
    void	*win_ptr;
    t_img   img;
}	t_data;

typedef struct {
    double x, y, z;
} Vector3;

typedef struct {
    Vector3 center;
    double radius;
} Sphere;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    Vector3 position;
    Vector3 direction;
    float fov;
    float aspect_ratio;
} Camera;

Vector3	vector_create(double x, double y, double z);
Vector3	vector_subtract(Vector3 v1, Vector3 v2);
double	vector_dot(Vector3 v1, Vector3 v2);
Vector3	vector_normalize(Vector3 v);
double	ray_sphere_intersect(Ray ray, Sphere sphere);
double	calculate_lighting(Vector3 point, Vector3 normal);

#endif