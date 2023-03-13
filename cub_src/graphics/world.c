/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:53:25 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/13 15:34:15 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub_include/cub.h"

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
	int				offset;
	t_co			hitp;
	int				i;
	mlx_texture_t	*t;

	t = data->walls[ray->side].texture;
	height = (((float)WIDTH / FOV * 27.0) / \
		(dist * cos(deg_to_rad(fix_ang(angle - data->player.angle)))));
	// if (height > HEIGHT)
	// 	height = HEIGHT;
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
