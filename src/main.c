/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/02/03 15:01:23 by mforstho      ########   odam.nl         */
=======
/*   Updated: 2023/02/03 15:03:58 by ageels        ########   odam.nl         */
>>>>>>> 4d57c2904efe68238a458fb7f77c3038d1d437a9
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse(argc, argv, &data))
		return (1);
<<<<<<< HEAD
	init_map_data(&data);
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
=======
	//init_map_data(open(argv[1], O_RDONLY), &data);
	data.mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", true);
>>>>>>> 4d57c2904efe68238a458fb7f77c3038d1d437a9
	if (!data.mlx)
		return (1);
	if (!display(&data))
		return (1);
	mlx_loop(data.mlx);
	//mlx_delete_image(data.mlx, ~all images~); // need a proper cleaning fun
	mlx_terminate(data.mlx);
	return (0);
}
