/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:26 by aogbi             #+#    #+#             */
/*   Updated: 2025/02/05 15:56:29 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

# define WIDTH 1024

typedef struct s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct s_vector3
{
	double x, y, z;
}						t_vector3;

typedef struct s_ambient_lightning
{
	double				ratio;
	int					rgb;
}						t_ambient_lightning;

typedef struct s_light
{
	t_vector3			position;
	double				brightness_ratio;
	int					rgb;
}						t_light;

typedef struct t_camera
{
	t_vector3			position;
	t_vector3			direction;
	float				fov;
}						t_camera;

typedef struct s_plane
{
	t_vector3			position;
	t_vector3			direction;
	int					rgb;
	struct s_plane		*next;
}						t_plane;

typedef struct s_sphere
{
	t_vector3			center;
	double				radius;
	int					rgb;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_cylinder
{
	t_vector3			center;
	t_vector3			axis;
	double				diameter;
	double				height;
	int					rgb;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_scenes
{
	t_ambient_lightning	*ambient;
	t_camera			*camera;
	t_light				*light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
}						t_scenes;

typedef struct s_ray
{
	t_vector3			origin;
	t_vector3			direction;
}						t_ray;

typedef struct s_info
{
	t_scenes			*scenes;
	t_vector3			pixel00_loc;
	t_vector3			pixel_delta_u;
	t_vector3			pixel_delta_v;
	t_vector3			viewport_upper_left;
	double				aspect_ratio;
	double				theta;
	double				viewport_height;
	double				viewport_width;
	t_vector3			viewport_u;
	t_vector3			viewport_v;
}						t_info;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_info				info;
}						t_data;

t_vector3				vector_create(double x, double y, double z);
t_vector3				vector_subtract(t_vector3 v1, t_vector3 v2);
double					vector_dot(t_vector3 v1, t_vector3 v2);
t_vector3				vector_add(t_vector3 a, t_vector3 b);
t_vector3				vector_normalize(t_vector3 v);
float				ray_sphere_intersect(t_ray ray, t_sphere *sphere);
// double					calculate_lighting(t_vector3 point,
// t_vector3 normal);
t_vector3				scale(t_vector3 v, float scalar);
t_scenes				*scene_description(char *file_name);
void					free_scenes(t_scenes *scenes);
bool					vector3_equal(t_vector3 a, t_vector3 b);
// float				ray_plane_intersect(t_ray ray, t_plane plane);
float plane_while(t_ray ray, t_plane **plane);
int		close_intersect(t_data *data, t_ray ray);
#endif