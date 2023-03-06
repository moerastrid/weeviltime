/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:44:57 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/06 16:39:15 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	gameloop(void *param)
{
	t_data	*data;

	data = param;
	draw_nose(data);
	move_hook(data);
	turn_hook(data);
}

//	data->mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
//	if (!data->mlx)
//		return (print_error("No MLX"));
//	display_background(data);
//	//init_raydata(data, &data->rays);
//	//init_textures(data);
//	//drawMap2D(data);
//	//mlx_image_to_window(data->mlx, data->rays.grid, 0, 0);
//	//draw_player(data);
//	//mlx_key_hook(data->mlx, &display_rays, data);
//	//mlx_loop_hook(data->mlx, &turn_hook, data);
//	//mlx_loop_hook(data->mlx, &move_hook, data);
//	mlx_loop_hook(data->mlx, &exit_hook, data);
//	//mlx_loop_hook(data->mlx, &hook, data);
//	mlx_loop(data->mlx);
//	mlx_terminate(data->mlx);
//	return (EXIT_SUCCESS);
