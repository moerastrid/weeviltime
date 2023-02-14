/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/14 16:30:05 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	leakfunc(void)
{
	system("leaks -q cub");
}

void	free_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(leakfunc);
	if (parse(argc, argv, &data))
		return (EXIT_FAILURE);
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data.mlx)
		return (EXIT_FAILURE);
	if (init_map_data(open(argv[1], O_RDONLY), &data) == EXIT_FAILURE)
	{
		mlx_terminate(data.mlx);
		return (EXIT_FAILURE);
	}
	if (!display(&data))
		return (EXIT_FAILURE);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_array(data.map_array);
	return (EXIT_SUCCESS);
}
