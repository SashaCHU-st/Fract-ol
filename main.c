#include "MLX42/include/MLX42/MLX42.h"
#include "ft_fractol.h"

static mlx_image_t *image;
int main (int argc, char **argv)
{

	t_fractol fractol;
	

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractol.name = argv[1];
		fractol_init(&fractol);
		//fractol_render(&fractol);
		mlx_loop(fractol.mlx_connection);
	}

	else
	{
		ft_putstr_fd("wrong variables", 2);
		exit(1);
	}

}
void fractol_init(t_fractol *fractol)
{
	mlx_t *mlx;
	if(!(fractol->mlx_connection = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return ;////
	if(!(fractol->mlx_window = mlx_image_to_window(mlx, image, 0, 0)))
	{
		mlx_close_window(mlx);
		free(fractol->mlx_connection);
	}
	if(!(fractol->img.image_ptr = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		free(fractol->mlx_connection);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}
}