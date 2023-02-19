/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/19 23:01:50 by astrid        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	leakfunc(void)
{
	system("leaks -q cub3D");
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

// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	atexit(leakfunc);
// 	if (setup(argc, argv, &data))
// 		return (EXIT_FAILURE);
// 	//if (!display(&data))
// 	//	return (EXIT_FAILURE);
// 	mlx_loop(data.mlx);
// 	//clean_everything(&data);
// 	return (EXIT_SUCCESS);
// }

	//mlx_delete_image(data.mlx, ~all images~); 
	// need a proper cleaning function


int	main(int argc, char **argv)
{
	t_data	data;

	atexit(leakfunc);
	if (argc <= 1)
	{
		printf("Need map\n");
		return (EXIT_FAILURE);
	}
	if (setup(argc, argv, &data))
		return (EXIT_FAILURE);
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data.mlx)
		return (EXIT_FAILURE);
	if (init_map(open(argv[1], O_RDONLY), &data) == EXIT_FAILURE)
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