/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 15:01:23 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse(argc, argv, &data))
		return (1);
	init_map_data(&data);
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data.mlx)
		return (1);
	if (!display(&data))
		return (1);
	mlx_loop(data.mlx);
	//mlx_delete_image(data.mlx, ~all images~); // need a proper cleaning fun
	mlx_terminate(data.mlx);
	return (0);
}
