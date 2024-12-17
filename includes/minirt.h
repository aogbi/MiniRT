/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:26 by aogbi             #+#    #+#             */
/*   Updated: 2024/12/16 18:40:45 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../Libft/libft.h"
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>

# define WIDTH 900
# define HEIGHT 600

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

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
}						t_data;

typedef struct s_vector3
{
	double x, y, z;
}						t_vector3;

typedef struct s_ambient_lightning
{
	int					ratio;
	int					rgb;
}						t_ambient_lightning;

typedef struct s_light
{
	t_vector3			position;
	int					brightness_ratio;
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
	double				radius;
	double				height;
	int					rgb;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_scenes
{
	t_ambient_lightning	ambient;
	t_camera			camera;
	t_light				light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
}						t_scenes;

typedef struct s_ray
{
	t_vector3			origin;
	t_vector3			direction;
}						t_ray;

t_vector3				vector_create(double x, double y, double z);
t_vector3				vector_subtract(t_vector3 v1, t_vector3 v2);
double					vector_dot(t_vector3 v1, t_vector3 v2);
t_vector3				vector_normalize(t_vector3 v);
double					ray_sphere_intersect(t_ray ray, t_sphere sphere);
double					calculate_lighting(t_vector3 point, t_vector3 normal);
t_vector3				scale(t_vector3 v, float scalar);

#endif