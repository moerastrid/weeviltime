/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:14:45 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/06 18:21:43 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	draw_nose(t_data *data)
{
	int			height;
	t_player	*p;
	t_line		nose;

	ft_fill(data->grid, data->mlx, 0);
	p = &data->player;
	height = data->mms / 4;
	nose.xa = p->x * data->mms;
	nose.ya = p->y * data->mms;
	nose.xb = p->x * data->mms + p->dirx * height * 2;
	nose.yb = p->y * data->mms + p->diry * height * 2;
	ft_line(data->grid, &nose, 0xF0F0F0FF);
}

void	check_direction(t_data	*data, int *x_step_dir, int *y_step_dir)
{
	float	dir;

	dir = data->player.direction;
	if (dir == 90 || dir == 270)
		*x_step_dir = 0;
	else if (dir > 90 && dir < 270)
		*x_step_dir = -1;
	else
		*x_step_dir = 1;
	if (dir == 0 || dir == 180)
		*y_step_dir = 0;
	else if (dir > 0 && dir < 180)
		*y_step_dir = -1;
	else
		*y_step_dir = 1;
}

int	draw_rays(t_data	*data)
{
	int		amount_of_rays;
	t_line	ray;
	int		x_step_dir;
	int		y_step_dir;
	int		next_line_x;
	int		next_line_y;

	//printf("drawing rays \n");
	amount_of_rays = RPD * FOV;
	if (amount_of_rays <= 0)
		return (EXIT_FAILURE);
	ray.xa = data->player.x;
	ray.ya = data->player.y;
	x_step_dir = 0;
	y_step_dir = 0;
	next_line_x = 0;
	next_line_y = 0;
	check_direction(data, &x_step_dir, &y_step_dir);
	//printf("step dir\tx:%d\ty:%d\n", x_step_dir, y_step_dir);
	if (x_step_dir == 0)
		ray.xb = ray.xa;
	if (y_step_dir == 0)
		ray.yb = ray.ya;

	next_line_x = (int)data->player.x;
	if (x_step_dir == 1)
		next_line_x += 1;
	next_line_y = (int)data->player.y;
	if (y_step_dir == 1)
		next_line_y += 1;

	while (next_line_x >= 0 && next_line_x <= data->max.x && x_step_dir != 0)
	{
		if (data->map[next_line_y * data->max.x + next_line_x] == 1)
			printf("hey\n");
		next_line_x += x_step_dir;
	}
	while (next_line_y >= 0 && next_line_y <= data->max.y && x_step_dir != 0)
	{
		if (data->map[next_line_y * data->max.x + next_line_x] == 1)
			printf("hoi\n");
		next_line_y += y_step_dir;
	}
	return (EXIT_SUCCESS);
}
