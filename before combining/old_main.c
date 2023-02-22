/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/20 14:54:09 by mforstho      ########   odam.nl         */
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

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(leakfunc);
	if (setup(argc, argv, &data))
		return (EXIT_FAILURE);
	if (!display(&data))
		return (EXIT_FAILURE);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_array(data.map_array);
	return (EXIT_SUCCESS);
}
