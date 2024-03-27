/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:07:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/03/27 10:13:12 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H
#define FT_FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"
#define WIDTH 512
#define HEIGHT 512


// typedef struct s_image 
// {
//     void *image_ptr; //pointer to image struct
//     char *pixels_ptr;//pointmg to actal pixels
//     int bpp;
//     int endian;
//     int line_len;
// } t_image;
typedef struct s_fractol
{
    mlx_t	*mlx;
    mlx_image_t* image;
    // double  centerx;
    // double  centery;
    double  min_x; // real
    double  max_x; //real
    double  min_y; // imaginary
    double  max_y; // imaginary
    int     max_iter;
    double  zoom;
} t_fractol;

 int    ft_strncmp(const char *s1, const char *s2, size_t n);
void    ft_putstr_fd(char *s, int fd);
void init(t_fractol *fractol);

#endif
