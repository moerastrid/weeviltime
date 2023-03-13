/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:44:57 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 18:09:28 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	draw_one_ray(t_data *data, t_ray *ray, unsigned int color)
{
	bool	display_ray;

	display_ray = false;
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		display_ray = true;
	if (display_ray == true)
	{
		ray->line.xa = (int)(ray->ax * data->mms);
		ray->line.ya = (int)(ray->ay * data->mms);
		ray->line.xb = (int)(ray->bx * data->mms);
		ray->line.yb = (int)(ray->by * data->mms);
		ft_line(data->grid, &ray->line, color);
	}
}

void	gameloop(void *param)
{
	t_data	*data;
	t_coll	*coll;

	data = param;
	coll = &data->collision;
	ft_fill(data->world, data->mlx, 0);
	forward_back_move_hook(data, coll);
	left_right_move_hook(data, coll);
	draw_nose(data);
	draw_rays(data);
	turn_hook(data);
}
