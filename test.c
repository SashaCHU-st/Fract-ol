#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ft_fractol.h"
#include "MLX42/include/MLX42/MLX42.h"

#define WIDTH 700
#define HEIGHT 700

static mlx_image_t* image;
static int centerX, centerY;
static int radius = 100;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void colors(void* param)
{
    (void)param;

    // Define the start and end colors for the gradient background
    int startColorR = 255;
    int startColorG = 255;
    int startColorB = 0;

    int endColorR = 0;
    int endColorG = 10;
    int endColorB = 0;

    // Calculate the distance from the center of the image to the edges
    double maxDistance = sqrt((WIDTH / 2) * (WIDTH / 2) + (HEIGHT / 2) * (HEIGHT / 2));

    // Iterate over each pixel in the image
    for (int x = 0; x < image->width; ++x)
    {
        for (int y = 0; y < image->height; ++y)
        {
            int dx = x - centerX;
            int dy = y - centerY;
            int distanceSquared = dx * dx + dy * dy;
            
            if(distanceSquared <= radius * radius)
            {
                int baseColorR = 31;
                int baseColorG = 224;
                int baseColorB = 230;


                double gradient = 1.0 - (sqrt(distanceSquared) / radius); // Линейный градиент от 1.0 (в центре) до 0.0 (на границе)
                
                // Вычисляем цвет внутри круга с использованием линейного градиента
                int colorR = baseColorR * gradient;
                int colorG = baseColorG * gradient;
                int colorB = baseColorB * gradient;

                // Устанавливаем цвет пикселя
                uint32_t color = ft_pixel(colorR, colorG, colorB, 255);
                mlx_put_pixel(image, x, y, color);

            }
            else 
            {
            // Calculate the distance of the current pixel from the center
            double distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));

            // Normalize the distance to range [0, 1]
            double normalizedDistance = distance / maxDistance;

            // Interpolate the color based on the normalized distance
            int colorR = startColorR + (endColorR - startColorR) * normalizedDistance;
            int colorG = startColorG + (endColorG - startColorG) * normalizedDistance;
            int colorB = startColorB + (endColorB - startColorB) * normalizedDistance;

            // Set the color of the current pixel
            uint32_t color = ft_pixel(colorR, colorG, colorB, 255);
            mlx_put_pixel(image, x, y, color);

            }
        }
    }
}




void ft_hook(void* param)
{
    mlx_t* mlx = param;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        centerY -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        centerY += 5;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        centerX -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        centerX += 5;

    // При нажатии клавиши "W" увеличиваем радиус круга
    if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
        radius *= 1.1; // Увеличиваем радиус круга на 5 пикселей
    }

    // При нажатии клавиши "S" уменьшаем радиус круга (но не меньше 0)
    if (mlx_is_key_down(mlx, MLX_KEY_S))
    {
        radius *= 1.1; // Уменьшаем радиус круга на 5 пикселей
        if (radius < 0)
            radius = 0; // Не позволяем радиусу быть отрицательным
    }

    mlx_loop_hook(mlx, colors, mlx);
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
    mlx_t* mlx;

    if (!(mlx = mlx_init(WIDTH, HEIGHT, "Fract-ol", true)))
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

    centerX = WIDTH / 2;
    centerY = HEIGHT / 2;

    mlx_loop_hook(mlx, colors, mlx);
    mlx_loop_hook(mlx, ft_hook, mlx);

    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}
