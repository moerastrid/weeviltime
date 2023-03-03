/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 22:04:17 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/03 22:12:41 by ageels        ########   odam.nl         */
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
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		p->direction -= 5;
		p->direction = fix_ang(p->direction);
	}
}