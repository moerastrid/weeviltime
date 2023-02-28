/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 15:24:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_include/cub.h"

static void	leakfunc(void)
{
	system("leaks -q cub3D");
}

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(leakfunc);
	if (parse(argc, argv, &data))
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data.mlx)
	{
		free_data(&data);
		return (print_error("No MLX"));
	}
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_data(&data);
	return (EXIT_SUCCESS);
}
