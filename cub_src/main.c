/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 18:09:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_include/cub.h"

//static void	leakfunc(void)
//{
//	system("leaks -q cub3D");
//}

static void	clean_data(t_data	*data)
{
	if (data->walls[NO].path)
		free(data->walls[NO].path);
	if (data->walls[SO].path)
		free(data->walls[SO].path);
	if (data->walls[WE].path)
		free(data->walls[WE].path);
	if (data->walls[EA].path)
		free(data->walls[EA].path);
	free(data->planes);
	free(data->walls);
}

int	main(int argc, char **argv)
{
	t_data	data;

	//atexit(leakfunc);
	if (parse(argc, argv, &data))
	{
		clean_data(&data);
		return (EXIT_FAILURE);
	}
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data.mlx)
	{
		clean_data(&data);
		return (print_error("No MLX"));
	}
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	clean_data(&data);
	return (EXIT_SUCCESS);
}
