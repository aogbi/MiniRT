/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:26 by aogbi             #+#    #+#             */
/*   Updated: 2025/03/02 01:04:12 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

# define WIDTH 1024
# define EPSILON 0.001F

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
	float	x;
	float	y;
	float	z;
}						t_vector3;

typedef struct s_ambient_lightning
{
	float				ratio;
	int					rgb;
}						t_ambient_lightning;

typedef struct s_light
{
	t_vector3			position;
	float				brightness_ratio;
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
	float				radius;
	int					rgb;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_cylinder
{
	t_vector3			center;
	t_vector3			axis;
	float				radias;
	float				height;
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

typedef struct s_save
{
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
}						t_save;

typedef struct s_info
{
	t_scenes			*scenes;
	t_save				save;
	t_vector3			pixel00_loc;
	t_vector3			pixel_delta_u;
	t_vector3			pixel_delta_v;
	t_vector3			viewport_upper_left;
	float				aspect_ratio;
	float				theta;
	float				viewport_height;
	float				viewport_width;
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

t_vector3				vector_create(float x, float y, float z);
t_vector3				vector_subtract(t_vector3 v1, t_vector3 v2);
float					vector_dot(t_vector3 v1, t_vector3 v2);
t_vector3				vector_add(t_vector3 a, t_vector3 b);
t_vector3				vector_normalize(t_vector3 v);
t_vector3				vector_cross(t_vector3 a, t_vector3 b);
float					ray_sphere_intersect(t_ray ray, t_sphere *sphere);
t_vector3				scale(t_vector3 v, float scalar);
t_scenes				*scene_description(char *file_name);
void					free_scenes(t_scenes *scenes);
bool					vector3_equal(t_vector3 a, t_vector3 b);
int						close_intersect(t_data *data, t_ray ray);
int						render(t_data *data);
float					spheres_while(t_ray ray, t_data *data);
float					plane_while(t_ray ray, t_data *data);
float					cyl_while(t_ray ray, t_data *data);
float					ray_plane_intersect(t_ray ray, t_plane plane);
float					intersect_cylinder(t_ray ray, t_cylinder *cyl);
int						calculate_plane_lighting(t_vector3 point,
							t_plane *plane, t_data *data);
int						calculate_sphere_lighting(t_vector3 point,
							t_sphere *sphere, t_data *data);
int						calculate_cylinder_lighting(t_vector3 point,
							t_cylinder *cyl, t_data *data);
bool					shadow(t_data *data, t_vector3 point,
							t_vector3 *light_direction);
float					vector_length(t_vector3 v);
void					hooks(t_data *data);
t_vector3				coordinates(char **array, int *flag);
int						ft_isfloat(char *str);
int						ft_isnum(char *str);
void					ft_str_array_free(char **array);
int						count_str_array(char **array);
int						init_ambient(char **array, t_scenes *scenes);
int						init_camera(char **array, t_scenes *scenes);
int						init_light(char **array, t_scenes *scenes);
int						init_sphere(char **array, t_scenes *scenes);
int						init_plane(char **array, t_scenes *scenes);
int						init_cylinder(char **array, t_scenes *scenes);
int						colors_range(char *str);
float					ft_atod(char *str);
#endif