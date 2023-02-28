/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 19:47:39 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_include/cub.h"

static void	leakfunc(void)
{
	system("leaks -q cub3D");
}

int32_t	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
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
	init_raydata(&data, &data.rays);
	init_textures(&data);
	drawMap2D(&data);
	mlx_image_to_window(data.mlx, data.rays.grid, 0, 0);
	draw_player(&data);

	mlx_key_hook(data.mlx, &input_hook, &data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);
	free_data(&data);
	return (EXIT_SUCCESS);
}
