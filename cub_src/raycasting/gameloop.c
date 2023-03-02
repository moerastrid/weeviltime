/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:44:57 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/02 14:45:33 by mforstho      ########   odam.nl         */
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

static void	get_collision(t_data *data, t_rays *rays, t_collision *coll)
{
	//	x offset to check map
	if (rays->pdx < 0)
		coll->xo = -(MMS / 3);
	else
		coll->xo = (MMS / 3);
	//	y offset to check map
	if (rays->pdy < 0)
		coll->yo = -(MMS / 3);
	else
		coll->yo = (MMS / 3);
	//	x position and offset
	coll->ipx = (data->player.pos_x + (MMS / 8)) / MMS;
	coll->ipx_add_xo = ((data->player.pos_x + (MMS / 8)) + coll->xo) / MMS;
	coll->ipx_sub_xo = ((data->player.pos_x + (MMS / 8)) - coll->xo) / MMS;
	//	y position and offset
	coll->ipy = (data->player.pos_y + (MMS / 8)) / MMS;
	coll->ipy_add_yo = ((data->player.pos_y + (MMS / 8)) + coll->yo) / MMS;
	coll->ipy_sub_yo = ((data->player.pos_y + (MMS / 8)) - coll->yo) / MMS;
}

static void	move_hook(void *param)
{
	t_data			*data;
	t_rays			*rays;
	mlx_t			*mlx;
	mlx_instance_t	*player;
	t_collision		*coll;

	data = param;
	rays = &data->rays;
	player = rays->player->instances;
	rays->ppddxx = rays->pdx * (MMS / 8);
	rays->ppddyy = rays->pdy * (MMS / 8);
	mlx = data->mlx;
	coll = &data->coll;
	get_collision(data, rays, coll);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		if (data->map[coll->ipy * data->max.x + coll->ipx_add_xo] == 0)
			data->player.pos_x += rays->ppddxx;
		if (data->map[coll->ipy_add_yo * data->max.x + coll->ipx] == 0)
			data->player.pos_y += rays->ppddyy;
		player->x = (int)data->player.pos_x;
		player->y = (int)data->player.pos_y;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		if (data->map[coll->ipy * data->max.x + coll->ipx_sub_xo] == 0)
			data->player.pos_x -= rays->ppddxx;
		if (data->map[coll->ipy_sub_yo * data->max.x + coll->ipx] == 0)
			data->player.pos_y -= rays->ppddyy;
		player->x = (int)data->player.pos_x;
		player->y = (int)data->player.pos_y;
	}
}

static void	turn_hook(void *param)
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
	// display_background(data);
	draw_player(data);
	mlx_key_hook(data->mlx, &display_rays, data);
	mlx_loop_hook(data->mlx, &turn_hook, data);
	mlx_loop_hook(data->mlx, &move_hook, data);
	mlx_loop_hook(data->mlx, &exit_hook, data);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
