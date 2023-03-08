/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:14:45 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/08 15:45:33 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	check_dir(t_data	*data, t_ray *ray, float angle)
{
	ray->dir.x = 0;
	ray->dir.y = 0;
	ray->start_x = data->player.x;
	ray->start_y = data->player.y;
	if (angle == 90 || angle == 270)
		ray->dir.x = 0;
	else if (angle > 90 && angle < 270)
		ray->dir.x = -1;
	else
		ray->dir.x = 1;
	if (angle == 0 || angle == 180)
		ray->dir.y = 0;
	else if (angle > 0 && angle < 180)
		ray->dir.y = -1;
	else
		ray->dir.y = 1;
	ray->end_x = data->player.x;
	if (ray->dir.x == 1)
		ray->end_x += 1;
	ray->end_y = data->player.y;
	if (ray->dir.y == 1)
		ray->end_y += 1;
}

void	draw_one_ray(t_data *data, t_ray *ray, unsigned int color)
{
	ray->line.xa = (int)(ray->start_x * data->mms);
	ray->line.ya = (int)(ray->start_y * data->mms);
	//ray->line.xb = (int)ray->end_x * data->mms;
	//ray->line.yb = (int)ray->end_y * data->mms;
	ray->line.xb = (int)(ray->end_x * data->mms);
	ray->line.yb = (int)(ray->end_y * data->mms);
	ft_line(data->grid, &ray->line, color);
	printf("ray start : %f %f\tend : %f %f\n", ray->start_x, ray->start_y, ray->end_x, ray->end_y);
}

void	ninety_degree_angle(t_data *data, t_ray *ray)
{
	if (ray->dir.x == 0)
	{
		while (data->map[(int)(ray->end_y)][(int)(ray->end_x)] != 1)
			ray->end_y += ray->dir.y;
		ray->end_y = (int)ray->end_y;
		if (ray->dir.y == -1)
			ray->end_y += 1;
	}
	if (ray->dir.y == 0)
	{
		while (data->map[(int)(ray->end_y)][(int)(ray->end_x)] != 1)
			ray->end_x += ray->dir.x;
		ray->end_x = (int)ray->end_x;
		if (ray->dir.x == -1)
			ray->end_x += 1;
	}
}

void	make_one_ray(t_data *data, float angle)
{
	t_ray	ray;

	//printf("angle %d : %f\n", i, angle);
	check_dir(data, &ray, angle);
	if (ray.dir.x == 0 || ray.dir.y == 0)
		ninety_degree_angle(data, &ray);
	draw_one_ray(data, &ray, 0xFF88FFFF);
}

void	draw_rays(t_data *data)
{
	//float	angle;
	//int		total_rays;
	//int		i;

	//angle = 0;
	//total_rays = FOV * RPD;
	//i = 0;
	//while (i < total_rays)
	//{
	//	angle = fix_ang(data->player.angle - (FOV / 2) + (i / (float)RPD));
	//	make_one_ray(data, angle, i);
	//	i++;
	//}
	make_one_ray(data, data->player.angle);
}
