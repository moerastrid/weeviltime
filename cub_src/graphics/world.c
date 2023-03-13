/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:53:25 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/13 21:07:21 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub_include/cub.h"

void	get_direction(t_data *data, t_ray *ray, float angle, int ray_nbr)
{
	ray->dir.x = 0;
	ray->dir.y = 0;
	ray->no = ray_nbr;
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

static int	get_hor_hitp(mlx_texture_t	*t, t_ray *ray)
{
	int	hor_hitp;

	hor_hitp = 0;
	if (fmod(ray->bx, 1) != 0)
		hor_hitp = fmod(ray->bx, 1) * t->width;
	else if (fmod(ray->by, 1) != 0)
		hor_hitp = fmod(ray->by, 1) * t->width;
	if (ray->side == WE || ray->side == SO)
		hor_hitp = t->width - hor_hitp;
	return (hor_hitp);
}

static unsigned int	get_color(mlx_texture_t	*t, t_co hitp)
{
	int	r;
	int	g;
	int	b;

	r = t->pixels[(hitp.y * t->width + hitp.x) * t->bytes_per_pixel];
	g = t->pixels[((hitp.y) * t->width + hitp.x) * t->bytes_per_pixel + 1];
	b = t->pixels[((hitp.y) * t->width + hitp.x) * t->bytes_per_pixel + 2];
	return (make_color(r, g, b));
}

void	draw_wall_line(t_data *data, t_ray *ray, float angle, float dist)
{
	float			height;
	float			offset;
	t_co			hitp;
	int				i;
	mlx_texture_t	*t;

	draw_one_ray(data, ray, COP);
	t = data->walls[ray->side].texture;
	height = (2.0001 * (WIDTH / FOV) * (HEIGHT / FOV)) / \
		((sqrt(dist) * cos(deg_to_rad(fix_ang(angle - data->player.angle)))));
	offset = ((float)HEIGHT / 2) - (height / 2);
	hitp.x = get_hor_hitp(t, ray);
	i = 0;
	while (i < height)
	{
		hitp.y = (i / height) * t->height;
		putpixel(data->world, ray->no, offset + i, get_color(t, hitp));
		i++;
	}
}
