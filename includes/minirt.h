/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:26 by aogbi             #+#    #+#             */
/*   Updated: 2024/10/25 13:58:11 by aogbi            ###   ########.fr       */
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

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
    int        width;
    int        height;
}	t_img;

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_img   img;
}	t_data;

#endif