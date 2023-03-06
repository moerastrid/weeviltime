/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 22:04:17 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/06 16:56:00 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	exit_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	turn_hook(void *param)
{
	t_data		*data;
	t_player	*p;

	data = param;
	p = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		p->direction += 5;
		p->direction = fix_ang(p->direction);
		p->dirx = cos(deg_to_rad(p->direction));
		p->diry = -sin(deg_to_rad(p->direction));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		p->direction -= 5;
		p->direction = fix_ang(p->direction);
		p->dirx = cos(deg_to_rad(p->direction));
		p->diry = -sin(deg_to_rad(p->direction));
	}
}

// static void	get_collision(t_data *data, t_rays *rays, t_collision *coll)
// {
// 	//	x offset to check map
// 	if (rays->pdx < 0)
// 		coll->xo = -(MMS / 3);
// 	else
// 		coll->xo = (MMS / 3);
// 	//	y offset to check map
// 	if (rays->pdy < 0)
// 		coll->yo = -(MMS / 3);
// 	else
// 		coll->yo = (MMS / 3);
// 	//	x position and offset
// 	coll->ipx = (data->player.x + (MMS / 8)) / MMS;
// 	coll->ipx_add_xo = ((data->player.x + (MMS / 8)) + coll->xo) / MMS;
// 	coll->ipx_sub_xo = ((data->player.x + (MMS / 8)) - coll->xo) / MMS;
// 	//	y position and offset
// 	coll->ipy = (data->player.y + (MMS / 8)) / MMS;
// 	coll->ipy_add_yo = ((data->player.y + (MMS / 8)) + coll->yo) / MMS;
// 	coll->ipy_sub_yo = ((data->player.y + (MMS / 8)) - coll->yo) / MMS;
// }

void	move_hook(void *param)
{
	t_data		*data;
	t_player	*p;

	data = param;
	p = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		p->x += p->dirx * (data->mms / 8);
		p->y += p->diry * (data->mms / 8);
		p->image->instances->x = (int)p->x - data->mms / 8;
		p->image->instances->y = (int)p->y - data->mms / 8;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		p->x -= p->dirx * (data->mms / 8);
		p->y -= p->diry * (data->mms / 8);
		p->image->instances->x = (int)p->x - data->mms / 8;
		p->image->instances->y = (int)p->y - data->mms / 8;
	}
}
