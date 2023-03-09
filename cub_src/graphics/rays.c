/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:14:45 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/09 17:54:42 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	check_dir(t_data	*data, t_ray *ray, float angle)
{
	ray->dir.x = 0;
	ray->dir.y = 0;
	ray->ax = data->player.x;
	ray->ay = data->player.y;
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
	ray->bx = data->player.x;
	ray->by = data->player.y;
}

void	draw_one_ray(t_data *data, t_ray *ray, unsigned int color)
{
	ray->line.xa = (int)(ray->ax * data->mms);
	ray->line.ya = (int)(ray->ay * data->mms);
	ray->line.xb = (int)(ray->bx * data->mms);
	ray->line.yb = (int)(ray->by * data->mms);
	ft_line(data->grid, &ray->line, color);
}

void	ninety_degree_angle(t_data *data, t_ray *ray)
{
	if (ray->dir.x == 0)
	{
		ray->by = (int)ray->by;
		while (data->map[(int)(ray->by)][(int)(ray->bx)] != 1)
			ray->by += ray->dir.y;
	}
	if (ray->dir.y == 0)
	{
		ray->bx = (int)ray->bx;
		while (data->map[(int)(ray->by)][(int)(ray->bx)] != 1)
			ray->bx += ray->dir.x;
	}
	if (ray->dir.y == -1)
		ray->by += 1;
	if (ray->dir.x == -1)
		ray->bx += 1;
}

float	find_pwr_distance_to_x_axis(t_data *data, t_ray *ray, float angle)
{
	float	pwr_distance;
	float	delta_x;
	float	delta_y;

	ray->bx = (int)ray->bx;
	if (ray->dir.x == 1)
		ray->bx++;
	while (ray->bx >= 0 && ray->bx < data->max.x)
	{
		ray->by = (ray->bx - ray->ax) * -tan(deg_to_rad(angle)) + ray->ay;
		if (ray->by < 0 || ray->by > data->max.y)
			return (FLT_MAX);
		if ((ray->dir.x == 1 && data->map[(int)ray->by][(int)ray->bx] == 1) || \
			(ray->dir.x == -1 && data->map[(int)ray->by][(int)ray->bx - 1] == 1))
			break ;
		ray->bx += ray->dir.x;
	}
	pwr_distance = pow(ray->bx - ray->ax, 2) + pow(ray->by - ray->ay, 2);
	return (pwr_distance);
}

float	find_pwr_distance_to_y_axis(t_data *data, t_ray *ray, float angle)
{
	float	pwr_distance;
	float	delta_x;
	float	delta_y;

	ray->by = (int)ray->by;
	if (ray->dir.y == 1)
		ray->by += 1;
	while (ray->by >= 0 && ray->by < data->max.y)
	{
		ray->bx = (ray->by - ray->ay) / -tan(deg_to_rad(angle)) + ray->ax;
		if (ray->bx < 0 || ray->bx > data->max.x)
			return (FLT_MAX);
		if ((ray->dir.y == 1 && data->map[(int)ray->by][(int)ray->bx] == 1) || \
			(ray->dir.y == -1 && data->map[(int)ray->by - 1][(int)ray->bx] == 1))
			break ;
		ray->by += ray->dir.y;
	}
	pwr_distance = pow(ray->bx - ray->ax, 2) + pow(ray->by - ray->ay, 2);
	return (pwr_distance);
}

void	make_one_ray(t_data *data, float angle)
{
	t_ray	ray_x;
	t_ray	ray_y;
	t_ray	*ray_final;
	float	pwr_distance_x;
	float	pwr_distance_y;

	check_dir(data, &ray_x, angle);
	check_dir(data, &ray_y, angle);
	if (ray_x.dir.x == 0 || ray_x.dir.y == 0)
	{
		ninety_degree_angle(data, &ray_x);
		ray_final = &ray_x;
	}
	else
	{
		pwr_distance_x = find_pwr_distance_to_x_axis(data, &ray_x, angle);
		pwr_distance_y = find_pwr_distance_to_y_axis(data, &ray_y, angle);
		if (pwr_distance_x < pwr_distance_y)
			ray_final = &ray_x;
		else
			ray_final = &ray_y;
	}
	draw_one_ray(data, ray_final, 0xFF88FFFF);
}

void	draw_rays(t_data *data)
{
	float	angle;
	int		total_rays;
	int		i;

	angle = 0;
	total_rays = FOV * RPD;
	i = 0;
	while (i < total_rays)
	{
		angle = fix_ang(data->player.angle - (FOV / 2) + (i / (float)RPD));
		make_one_ray(data, angle);
		i++;
	}
}
