/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 16:25:59 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse(argc, argv, &data))
		return (1);
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", true);
	//init_map_data(open(argv[1], O_RDONLY), &data);
	if (!data.mlx)
		return (1);
	if (!display(&data))
		return (1);
	mlx_loop(data.mlx);
	//mlx_delete_image(data.mlx, ~all images~); // need a proper cleaning fun
	mlx_terminate(data.mlx);
	return (0);
}
