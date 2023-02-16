/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/16 21:17:52 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	leakfunc(void)
{
	system("leaks -q cub3D");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (setup(argc, argv, &data))
		return (EXIT_FAILURE);
	if (!display(&data))
		return (EXIT_FAILURE);
	mlx_loop(data.mlx);
	//clean_everything(&data);
	return (EXIT_SUCCESS);
}

	//mlx_delete_image(data.mlx, ~all images~); 
	// need a proper cleaning function
