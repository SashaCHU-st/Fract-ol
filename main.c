/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:09:33 by aheinane          #+#    #+#             */
/*   Updated: 2024/03/05 16:34:56 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <mlx.h>

// int main (int argc, char **argv)
// {
// 	if(argc == 2)
		
// 	return(0);
		
// }
int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}