/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/14 00:07:53 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse(argc, argv, &data))
		return (1);
	if (!display(&data))
	{
		printf("no dis \n");
		return (1);
	}
	mlx_loop(data.mlx);
	free(data.map_array);
	mlx_delete_image(data.mlx, data.walls.wall_north);
	mlx_delete_image(data.mlx, data.walls.wall_south);
	mlx_delete_image(data.mlx, data.walls.wall_west);
	mlx_delete_image(data.mlx, data.walls.wall_east);
	mlx_terminate(data.mlx);
	return (0);
}

	//mlx_delete_image(data.mlx, ~all images~); 
	// need a proper cleaning function
