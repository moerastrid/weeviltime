/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:44:57 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 20:56:42 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	draw_one_ray(t_data *data, t_ray *ray, unsigned int color)
{
	bool	display_ray;

	display_ray = false;
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		display_ray = true;
	if (display_ray == true && data->minimap == true)
	{
		ray->line.xa = (int)(ray->ax * data->mms);
		ray->line.ya = (int)(ray->ay * data->mms);
		ray->line.xb = (int)(ray->bx * data->mms);
		ray->line.yb = (int)(ray->by * data->mms);
		ft_line(data->raygrid, &ray->line, color);
	}
}

void	gameloop(void *param)
{
	t_data	*data;
	t_coll	*coll;

	data = param;
	coll = &data->collision;
	ft_fill(data->world, data->mlx, 0);
	forward_move_hook(data, coll);
	back_move_hook(data, coll);
	left_move_hook(data, coll);
	right_move_hook(data, coll);
	draw_nose(data);
	draw_rays(data);
	turn_hook(data);
}

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
