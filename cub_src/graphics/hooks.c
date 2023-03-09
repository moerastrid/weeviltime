/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 22:04:17 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/09 15:56:10 by mforstho      ########   odam.nl         */
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

void	turn_hook(t_data *data)
{
	t_player	*p;

	p = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		p->angle += 5;
		p->angle = fix_ang(p->angle);
		p->dirx = cos(deg_to_rad(p->angle));
		p->diry = -sin(deg_to_rad(p->angle));
		p->lrx = cos(deg_to_rad(fix_ang(p->angle + 90.0)));
		p->lry = -sin(deg_to_rad(fix_ang(p->angle + 90.0)));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		p->angle -= 5;
		p->angle = fix_ang(p->angle);
		p->dirx = cos(deg_to_rad(p->angle));
		p->diry = -sin(deg_to_rad(p->angle));
		p->lrx = cos(deg_to_rad(fix_ang(p->angle + 90.0)));
		p->lry = -sin(deg_to_rad(fix_ang(p->angle + 90.0)));
	}
}

void	forward_back_move_hook(t_data *data)
{
	t_player	*p;

	p = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		p->x += (0.01 * SPEED) * p->dirx;
		p->y += (0.01 * SPEED) * p->diry;
		p->image->instances->x = p->x * data->mms - data->mms / 8;
		p->image->instances->y = p->y * data->mms - data->mms / 8;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		p->x -= (0.01 * SPEED) * p->dirx;
		p->y -= (0.01 * SPEED) * p->diry;
		p->image->instances->x = p->x * data->mms - data->mms / 8;
		p->image->instances->y = p->y * data->mms - data->mms / 8;
	}
}

void	left_right_move_hook(t_data *data)
{
	t_player	*p;

	p = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		p->x += (0.01 * SPEED) * p->lrx;
		p->y += (0.01 * SPEED) * p->lry;
		p->image->instances->x = p->x * data->mms - data->mms / 8;
		p->image->instances->y = p->y * data->mms - data->mms / 8;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		p->x -= (0.01 * SPEED) * p->lrx;
		p->y -= (0.01 * SPEED) * p->lry;
		p->image->instances->x = p->x * data->mms - data->mms / 8;
		p->image->instances->y = p->y * data->mms - data->mms / 8;
	}
}
