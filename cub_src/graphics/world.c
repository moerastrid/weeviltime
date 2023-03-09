/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:53:25 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/09 20:12:43 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub_include/cub.h"

void	draw_wall_line(t_data *data, int raynbr, float angle, float dist, int side)
{
	t_line	line;
	float	p;
	float	height;
	float	offset;
	unsigned int color;

	p = dist * cos(deg_to_rad(fix_ang(angle - data->player.angle)));
	height = (((float)WIDTH / FOV * 27.0) / p);
	if (height > HEIGHT)
		height = HEIGHT;
	offset = ((float)HEIGHT / 2) - (height / 2);
	line.xa = (float)raynbr;
	line.ya = offset;
	line.xb = (float)raynbr;
	line.yb = offset + height;
	color = 0xFFFFFFFF;
	if (side == NO)
		color = 0xBB2222FF;
	if (side == SO)
		color = 0xBBBB22FF;
	if (side == WE)
		color = 0x2222BBFF;
	if (side == EA)
		color = 0x22BBBBFF;
	ft_line(data->world, &line, color);
}
