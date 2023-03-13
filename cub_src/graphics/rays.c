/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:14:45 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 19:50:02 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static void	check_dir(t_data *data, t_ray *ray, float angle)
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

static float	ninety_degree_angle(t_data *data, t_ray *ray, float angle)
{
	float	dist;

	if (ray->dir.x == 0)
	{
		ray->by = (int)ray->by;
		while (data->map[(int)(ray->by)][(int)(ray->bx)] != 1)
			ray->by += ray->dir.y;
		dist = ray->by - ray->ay;
	}
	if (ray->dir.y == 0)
	{
		ray->bx = (int)ray->bx;
		while (data->map[(int)(ray->by)][(int)(ray->bx)] != 1)
			ray->bx += ray->dir.x;
		dist = ray->bx - ray->ax;
	}
	if (ray->dir.y == -1)
		ray->by += 1;
	if (ray->dir.x == -1)
		ray->bx += 1;
	if (angle == 0)
		ray->side = EA;
	if (angle == 90)
		ray->side = NO;
	if (angle == 180)
		ray->side = WE;
	if (angle == 270)
		ray->side = SO;
	return (pow(dist, 2));
}

static float	find_powdist_to_x_axis(t_data *data, t_ray *ray, float angle)
{
	float	powdist;

	ray->bx = (int)ray->bx;
	if (ray->dir.x == 1)
		ray->bx++;
	while (ray->bx > 0 && ray->bx < data->max.x)
	{
		ray->by = (ray->bx - ray->ax) * -tan(deg_to_rad(angle)) + ray->ay;
		if (ray->by < 0 || ray->by > data->max.y)
			return (FLT_MAX);
		if ((ray->dir.x == 1 && data->map[(int)ray->by][(int)ray->bx] == 1) || \
			(ray->dir.x == -1 && \
			data->map[(int)ray->by][(int)ray->bx - 1] == 1))
			break ;
		ray->bx += ray->dir.x;
	}
	powdist = pow(ray->bx - ray->ax, 2) + pow(ray->by - ray->ay, 2);
	if (ray->dir.x == -1)
		ray->side = WE;
	if (ray->dir.x == 1)
		ray->side = EA;
	return (powdist);
}

static float	find_powdist_to_y_axis(t_data *data, t_ray *ray, float angle)
{
	float	powdist;

	ray->by = (int)ray->by;
	if (ray->dir.y == 1)
		ray->by ++;
	while (ray->by > 0 && ray->by < data->max.y)
	{
		ray->bx = (ray->by - ray->ay) / -tan(deg_to_rad(angle)) + ray->ax;
		if (ray->bx < 0 || ray->bx > data->max.x)
			return (FLT_MAX);
		if ((ray->dir.y == 1 && data->map[(int)ray->by][(int)ray->bx] == 1) || \
			(ray->dir.y == -1 && \
			data->map[(int)ray->by - 1][(int)ray->bx] == 1))
			break ;
		ray->by += ray->dir.y;
	}
	powdist = pow(ray->bx - ray->ax, 2) + pow(ray->by - ray->ay, 2);
	if (ray->dir.y == -1)
		ray->side = NO;
	if (ray->dir.y == 1)
		ray->side = SO;
	return (powdist);
}

void	make_one_ray(t_data *data, float angle, int ray_nbr, t_ray *ray_final)
{
	t_ray	ray_x;
	t_ray	ray_y;
	float	powdist_x;
	float	powdist_y;

	powdist_x = FLT_MAX;
	powdist_y = FLT_MAX;
	check_dir(data, &ray_x, angle);
	check_dir(data, &ray_y, angle);
	if (ray_x.dir.x == 0 || ray_x.dir.y == 0)
	{
		powdist_x = ninety_degree_angle(data, &ray_x, angle);
		ray_final = &ray_x;
	}
	else
	{
		powdist_x = find_powdist_to_x_axis(data, &ray_x, angle);
		powdist_y = find_powdist_to_y_axis(data, &ray_y, angle);
		if (powdist_x < powdist_y)
			ray_final = &ray_x;
		else
			ray_final = &ray_y;
	}
	if (powdist_y < powdist_x)
		powdist_x = powdist_y;
	ray_final->no = ray_nbr;
	draw_wall_line(data, ray_final, angle, powdist_x);
}
