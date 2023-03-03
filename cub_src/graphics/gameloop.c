/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:44:57 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/03 15:10:24 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

//	graphics

static void	exit_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

int	gameloop(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data->mlx)
		return (print_error("No MLX"));
	if (draw_world(data))
	{
		mlx_terminate(data->mlx);
		return (EXIT_FAILURE);
	}
	if (draw_minimap(data))
	{
		mlx_terminate(data->mlx);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(data->mlx, &exit_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}

//int	gameloop(t_data *data)
//{
	
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
//}
