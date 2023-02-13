/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/13 18:08:43 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse(argc, argv, &data))
		return (1);
	if (!display(&data))
		return (1);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

	//mlx_delete_image(data.mlx, ~all images~); 
	// need a proper cleaning function
