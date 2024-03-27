/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:58:01 by aheinane          #+#    #+#             */
/*   Updated: 2024/03/27 12:00:59 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void init(t_fractol *fractol)
{
    // fractol->centerx = 0;
    // fractol->centery = 0;
    fractol->min_x = -2.0; // real
    fractol->max_x = 1.0;  // real
    fractol->min_y = -1.0; // imaginary
    fractol->max_y = 1.0;  // imaginary
    fractol->max_iter = 200;
    fractol->zoom = 1.5;
}

void draw_mandelbrot(void *param)
{
    t_fractol *fractol;
	fractol = (t_fractol *) param;
    int x, y;
    double zx, zy, tmp;
    int32_t color;

    y = 0;
    while (y < HEIGHT)
	{
        x = 0;
        while (x < WIDTH)
		{
            zx = 0;
            zy = 0;
            double c_real = fractol->min_x + (x * (fractol->max_x - fractol->min_x) / WIDTH);
            double c_imaginary = fractol->min_y + (y * (fractol->max_y - fractol->min_y) / HEIGHT);
            int iter = 0;
            while (zx * zx + zy * zy < 4 && iter < fractol->max_iter)
			{
                tmp = zx * zx - zy * zy + c_real;
                zy = 2.0 * zx * zy + c_imaginary;
                zx = tmp;
                iter++;
            }
            if (iter < fractol->max_iter)
            {
               double iter_smooth = iter + 1 - log2(log2(sqrt(zx * zx + zy * zy)));
                int r = (int)(iter_smooth * 20) % 256;
                int g = (int)(iter_smooth * 30) % 256;
                int b = (int)(iter_smooth * 40) % 256;
                color = ft_pixel(r, g, b, 255);
            }
            else
            {
                color = ft_pixel(0, 0, 0, 255);
            }
            mlx_put_pixel(fractol->image, x, y, color);
            x++;
        }
        y++;
    }
    mlx_image_to_window(fractol->mlx, fractol->image, 0, 0);
}

int main(int argc, char **argv) {
    t_fractol fractol;

    if (argc != 2 || ft_strncmp(argv[1], "M", 10) != 0)
    {
        ft_putstr_fd("Wrong, write M for Mandelbrot \n", 2);
        return EXIT_FAILURE;
    }
    fractol.mlx = mlx_init(WIDTH, HEIGHT, "Mandelbrot Set", true);
    if (!fractol.mlx)
    {
        ft_putstr_fd("Failed to initialize mlx\n", 2);
        return EXIT_FAILURE;
    }

    fractol.image = mlx_new_image(fractol.mlx, WIDTH, HEIGHT);
    if (!fractol.image)
    {
        ft_putstr_fd("Failed to create image\n", 2);
        mlx_close_window(fractol.mlx);
        return EXIT_FAILURE;
    }
    init(&fractol);
    draw_mandelbrot(&fractol);
    mlx_loop(fractol.mlx);
    mlx_terminate(fractol.mlx);

    return EXIT_SUCCESS;
}

