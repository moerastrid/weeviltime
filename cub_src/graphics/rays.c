/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:14:45 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/09 16:34:44 by ageels        ########   odam.nl         */
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
	ray->end_y = data->player.y;
}

void	draw_one_ray(t_data *data, t_ray *ray, unsigned int color)
{
	ray->line.xa = (int)(ray->start_x * data->mms);
	ray->line.ya = (int)(ray->start_y * data->mms);
	ray->line.xb = (int)(ray->end_x * data->mms);
	ray->line.yb = (int)(ray->end_y * data->mms);
	ft_line(data->grid, &ray->line, color);
}

void	ninety_degree_angle(t_data *data, t_ray *ray)
{
	if (ray->dir.x == 0)
	{
		ray->end_y = (int)ray->end_y;
		while (data->map[(int)(ray->end_y)][(int)(ray->end_x)] != 1)
			ray->end_y += ray->dir.y;
	}
	if (ray->dir.y == 0)
	{
		ray->end_x = (int)ray->end_x;
		while (data->map[(int)(ray->end_y)][(int)(ray->end_x)] != 1)
			ray->end_x += ray->dir.x;
	}
	if (ray->dir.y == -1)
		ray->end_y += 1;
	if (ray->dir.x == -1)
		ray->end_x += 1;
}

float	find_pwr_distance_to_x_axis(t_data *data, t_ray *ray, float angle)
{
	float	pwr_distance;
	float	delta_x;
	float	delta_y;

	if (ray->dir.x == 1)
	{
		ray->end_x = (int)ray->end_x + 1;
		while(ray->end_x >= 0 && ray->end_x < data->max.x)
		{
			ray->end_y = (ray->end_x - ray->start_x) * -tan(deg_to_rad(angle)) + ray->start_y;
			if (ray->end_y < 0 || ray->end_y > data->max.y)
				return (FLT_MAX);
			if (data->map[(int)ray->end_y][(int)ray->end_x] == 1)
				break ;
			ray->end_x += ray->dir.x;
		}
	}
	else if (ray->dir.x == -1)
	{
		ray->end_x = (int)ray->end_x;
		while(ray->end_x >= 0 && ray->end_x < data->max.x)
		{
			ray->end_y = (ray->end_x - ray->start_x) * -tan(deg_to_rad(angle)) + ray->start_y;
			if (ray->end_y < 0 || ray->end_y > data->max.y)
				return (FLT_MAX);
			if (data->map[(int)ray->end_y][(int)ray->end_x] == 1)
				break ;
			ray->end_x += ray->dir.x;
		}
	}
	printf("x-axis coords: %f, %f\n", ray->end_x, ray->end_y);
	pwr_distance = ray->end_x * ray->end_x + ray->end_y * ray->end_y;
	return (pwr_distance);
}

float	find_pwr_distance_to_y_axis(t_data *data, t_ray *ray, float angle)
{
	float	pwr_distance;
	float	delta_x;
	float	delta_y;

	if (ray->dir.y == 1)
	{
		ray->end_y = (int)ray->end_y + 1;
		while (ray->end_y >= 0 && ray->end_y < data->max.y)
		{
			ray->end_x = (ray->end_y - ray->start_y) / -tan(deg_to_rad(angle)) + ray->start_x;
			if (ray->end_x < 0 || ray->end_x > data->max.x)
				return (FLT_MAX);
			if (data->map[(int)ray->end_y][(int)ray->end_x] == 1)
				break ;
			ray->end_y += ray->dir.y;
		}
	}
	else if (ray->dir.y == -1)
	{
		ray->end_y = (int)ray->end_y ;
		while (ray->end_y >= 0 && ray->end_y < data->max.y)
		{
			ray->end_x = (ray->end_y - ray->start_y) / -tan(deg_to_rad(angle)) + ray->start_x;
			if (ray->end_x < 0 || ray->end_x > data->max.x)
				return (FLT_MAX);
			if (data->map[(int)ray->end_y][(int)ray->end_x] == 1)
				break ;
			ray->end_y += ray->dir.y;
		}
	}
	printf("y-axis coords: %f, %f\n", ray->end_x, ray->end_y);
	pwr_distance = ray->end_x * ray->end_x + ray->end_y * ray->end_y;
	return (pwr_distance);
}

void	make_one_ray(t_data *data, float angle)
{
	t_ray	ray_x;
	t_ray	ray_y;
	t_ray	ray_final;
	float	pwr_distance_x;
	float	pwr_distance_y;

	//printf("angle %d : %f\n", i, angle);
	check_dir(data, &ray_x, angle);
	check_dir(data, &ray_y, angle);
	check_dir(data, &ray_final, angle);
	if (ray_final.dir.x == 0 || ray_final.dir.y == 0)
		ninety_degree_angle(data, &ray_final);
	else
	{
		pwr_distance_x = find_pwr_distance_to_x_axis(data, &ray_x, angle);
		pwr_distance_y = find_pwr_distance_to_y_axis(data, &ray_y, angle);
		if (pwr_distance_x < pwr_distance_y)
			find_pwr_distance_to_x_axis(data, &ray_final, angle);
		else
			find_pwr_distance_to_y_axis(data, &ray_final, angle);
	}
	printf("final coords: %f, %f\n", ray_final.end_x, ray_final.end_y);
	draw_one_ray(data, &ray_final, 0xFF88FFFF);
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
	//	make_one_ray(data, angle);
	//	i++;
	//}
	make_one_ray(data, data->player.angle);
}
