/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/02 21:50:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"
#define WIDTH 1024
#define HEIGHT 1024

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse(argc, argv, &data))
		return (1);
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", true);
	if (!data.mlx)
		return (1);
	printf("MLX ptr inside main: %p\n", &data.mlx);
	if (!display(&data))
		return (1);
	mlx_loop(data.mlx);
	//mlx_delete_image(data.mlx, ~all images~); // need a proper cleaning fun
	mlx_terminate(data.mlx);
	return (0);
}
