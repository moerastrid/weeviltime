/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:53:25 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/09 19:04:36 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub_include/cub.h"

void	draw_wall_line(t_data *data, int raynbr, float angle, float dist)
{
	t_line	line;
	float	p;
	float	height;
	float	offset;

	p = dist * cos(deg_to_rad(fix_ang(angle - data->player.angle)));
	height = (((float)WIDTH / FOV * 27.0) / p);
	if (height > HEIGHT)
		height = HEIGHT;
	offset = ((float)HEIGHT / 2) - (height / 2);
	line.xa = (float)raynbr;
	line.ya = offset;
	line.xb = (float)raynbr;
	line.yb = offset + height;
	ft_line(data->world, &line, 0xFFFFFFFF);
}
