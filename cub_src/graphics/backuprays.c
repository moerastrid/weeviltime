/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   backuprays.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 15:14:45 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/08 16:54:04 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	check_direction(t_data	*data, t_ray *ray, float angle)
{
	ray->step_dir.x = 0;
	ray->step_dir.y = 0;
	ray->next_pos.x = 0;
	ray->next_pos.y = 0;
	if (angle == 90 || angle == 270)
		ray->step_dir.x = 0;
	else if (angle > 90 && angle < 270)
		ray->step_dir.x = -1;
	else
		ray->step_dir.x = 1;
	if (angle == 0 || angle == 180)
		ray->step_dir.y = 0;
	else if (angle > 0 && angle < 180)
		ray->step_dir.y = -1;
	else
		ray->step_dir.y = 1;
	ray->next_pos.x = data->player.x;
	if (ray->step_dir.x == 1)
		ray->next_pos.x += 1;
	ray->next_pos.y = data->player.y;
	if (ray->step_dir.y == 1)
		ray->next_pos.y += 1;
}

static void	scale_line(t_data *data, t_line *line)
{
	if (line->xa != 0)
		line->xa *= data->mms;
	if (line->ya != 0)
		line->ya *= data->mms;
	if (line->xb != 0)
		line->xb *= data->mms;
	if (line->yb != 0)
		line->yb *= data->mms;
}

void	ninety_degree_angle(t_data *data, t_ray *ray)
{
	if (ray->step_dir.x == 0)
	{
		ray->line.xb = ray->next_pos.x;
		while (data->map[(data->max.x * ray->next_pos.y + ray->next_pos.x)] != 1)
			ray->next_pos.y += ray->step_dir.y;
		ray->line.yb = ray->next_pos.y;
		if (ray->step_dir.y == -1)
			ray->line.yb++;
	}
	if (ray->step_dir.y == 0)
	{
		ray->line.yb = ray->next_pos.y;
		while (data->map[(data->max.x * ray->next_pos.y + ray->next_pos.x)] != 1)
			ray->next_pos.x += ray->step_dir.x;
		ray->line.xb = ray->next_pos.x;
		if (ray->step_dir.x == -1)
			ray->line.xb++;
	}
}

void	compare_dist(t_data *data, t_ray *ray, float angle)
{
	float	dist_to_hor_wall;
	float	hor_x;
	float	hor_y;
	float	hor_b;
	float	hor_dx;
	float	hor_dy;
	float	ver_x = 0;
	float	ver_y = 0;
	//float	ver_b = 0;
	//float	ver_dx = 0;
	//float	ver_dy = 0;
	float	dist_to_ver_wall;

	dist_to_hor_wall = INT_MAX;
	dist_to_ver_wall = INT_MAX;
	hor_y = 0;
	hor_b = (data->player.y - (deg_to_rad(tan(angle)) * data->player.x));
	while (ray->next_pos.x >= 0 && ray->next_pos.x <= data->max.x)
	{
		hor_x = ray->next_pos.x;
		hor_y = tan(deg_to_rad(angle)) * ray->next_pos.x + hor_b;
		if (data->map[(int)(hor_y * data->max.x + ray->next_pos.x)] == 1)
			break ;
		ray->next_pos.x += ray->step_dir.x;
	}
	hor_dx = data->player.x - ray->next_pos.x;
	hor_dy = data->player.y - hor_y;
	dist_to_hor_wall = (hor_dy * hor_dy) + (hor_dx * hor_dx);
	printf("hor_y %f,\t  dist_to_hor_wall: %f \n", hor_y, sqrt(dist_to_hor_wall));
	if (dist_to_hor_wall < dist_to_ver_wall)
	{
		ray->line.xb = hor_x; // = ray->next_pos.x
		ray->line.yb = hor_y;
	}
	else
	{
		ray->line.xb = ver_x;
		ray->line.yb = ver_y;
	}
}

void	draw_one_ray(t_data *data, float angle)
{
	t_ray	ray;

	ray.line.xa = data->player.x;
	ray.line.ya = data->player.y;
	ray.line.xb = 0;
	ray.line.yb = 0;
	check_direction(data, &ray, angle);
	printf("step dir\tx %d\ty %d\n", ray.step_dir.x, ray.step_dir.y);
	if (ray.step_dir.x == 0 || ray.step_dir.y == 0)
		ninety_degree_angle(data, &ray);
	else
		compare_dist(data, &ray, angle);
	//	printf("step dir\tx:%d\ty:%d\nnext pos\tx:%d\ty:%d\n", ray.step_dir.x, ray.step_dir.y, ray.next_pos.x, ray.next_pos.y);
	if (ray.line.xb != 0 && ray.line.yb != 0)
		printf("ray begin\tx:%f\ty:%f\nray end \tx:%f\ty:%f\nangle: %f \n", ray.line.xa, ray.line.ya, ray.line.xb, ray.line.yb, angle);
	scale_line(data, &ray.line);
	ft_line(data->grid, &ray.line, 0x5588FFFF);
}

int	draw_rays(t_data	*data)
{
	int		amount_of_rays;
	int		i;
	float	angle;
	float	float_rpd;

	float_rpd = RPD;
	amount_of_rays = FOV * float_rpd;
	if (amount_of_rays <= 0)
		return (EXIT_FAILURE);
	i = 0;
	angle = fix_ang(data->player.direction - (FOV / 2));
	while (i < amount_of_rays)
	{
		angle = data->player.direction - (FOV / 2) + (i / float_rpd);
		draw_one_ray(data, angle);
		i++;
	}
	//draw_one_ray(data, data->player.direction);
	return (EXIT_SUCCESS);
}
