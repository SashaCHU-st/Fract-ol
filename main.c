#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "ft_fractol.h"
#include "MLX42/include/MLX42/MLX42.h"

static mlx_image_t* image;
// Constants for Mandelbrot set iteration
#define maxIterations 1000
#define minReal -2
#define maxReal 2
#define minImaginary -2
#define maxImaginary 2

// Global variables to track the zoom level
static double zoomLevel = 1.0;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// Function to calculate whether a complex number is in the Mandelbrot set
int mandelbrot(double real, double imaginary)
{
    double zReal = real;
    double zImaginary = imaginary;
    int iterations = 0;

    while (iterations < maxIterations)
    {
        double zRealSquared = zReal * zReal;
        double zImaginarySquared = zImaginary * zImaginary;

        if (zRealSquared + zImaginarySquared > 4)
        {
            break;
        }

        double newReal = zRealSquared - zImaginarySquared + real;
        double newImaginary = 2 * zReal * zImaginary + imaginary;

        zReal = newReal;
        zImaginary = newImaginary;

        iterations++;
    }

    return iterations;
}

// Function to draw the Mandelbrot set
void draw_mandelbrot(void* param)
{
    (void)param;

    double realFactor = (maxReal - minReal) / (WIDTH * zoomLevel);
    double imaginaryFactor = (maxImaginary - minImaginary) / (HEIGHT * zoomLevel);

    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            double real = minReal + x * realFactor;
            double imaginary = minImaginary + y * imaginaryFactor;

            int iterations = mandelbrot(real, imaginary);

            uint32_t color;
            if (iterations == maxIterations)
            {
                // Pixel is in the Mandelbrot set, color it black
                color = ft_pixel(0, 0, 0, 255);
            }
            else
            {
                // Pixel is not in the Mandelbrot set, color it based on the number of iterations
                int r = iterations % 256;
                int g = (iterations * 3) % 256;
                int b = (iterations * 5) % 256;
                color = ft_pixel(r, g, b, 255);
            }

            mlx_put_pixel(image, x, y, color);
        }
    }
}

void ft_hook(void* param)
{
    mlx_t* mlx = param;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);

    // Zoom in
    if (mlx_is_key_down(mlx, MLX_KEY_W))
        zoomLevel *= 1.0;

    // Zoom out
    if (mlx_is_key_down(mlx, MLX_KEY_S))
        zoomLevel /= 1.0;

    mlx_loop_hook(mlx, draw_mandelbrot, mlx);
}

int main(void)
{
    mlx_t* mlx;

    if (!(mlx = mlx_init(WIDTH, HEIGHT, "Mandelbrot Set", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }
    if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    } 
    if (mlx_image_to_window(mlx, image, 0, 0) == -1)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }

    mlx_loop_hook(mlx, draw_mandelbrot, mlx);
    mlx_loop_hook(mlx, ft_hook, mlx);

    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}
