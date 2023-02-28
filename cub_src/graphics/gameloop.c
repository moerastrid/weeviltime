/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:44:57 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 21:08:22 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static void	move_sideways_hook(void *param)
{
	t_data	*data;
	t_rays	*rays;

	data = param;
	rays = &data->rays;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		rays->pa += 5;
		rays->pa = fix_ang(rays->pa);
		rays->pdx = cos(deg_to_rad(rays->pa));
		rays->pdy = -sin(deg_to_rad(rays->pa));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		rays->pa -= 5;
		rays->pa = fix_ang(rays->pa);
		rays->pdx = cos(deg_to_rad(rays->pa));
		rays->pdy = -sin(deg_to_rad(rays->pa));
	}
}


int	gameloop(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data->mlx)
		return (print_error("No MLX"));
	init_raydata(data, &data->rays);
	init_textures(data);
	drawMap2D(data);
	mlx_image_to_window(data->mlx, data->rays.grid, 0, 0);
	draw_player(data);
	mlx_key_hook(data->mlx, &display_rays, data);
	mlx_loop_hook(data->mlx, &move_sideways_hook, data);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
