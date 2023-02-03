/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:48:59 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 16:42:19 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

unsigned int	make_color(int r, int g, int b)
{
	return ((unsigned int)(r << 24 | g << 16 | b << 8 | 0xFF));
}

void	fill(t_skyfl plane)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (j < plane.img->height)
	{
		i = 0;
		while (i < plane.img->width)
		{
			wrap_putpixel(plane.img, i, j, plane.color);
			i++;
		}
		j++;
	}
}

bool	background(t_data *data)
{
	data->sky.img = mlx_new_image(data->mlx, data->mlx->width, (data->mlx->height / 2));
	data->floor.img = mlx_new_image(data->mlx, data->mlx->width, (data->mlx->height / 2));
	if (!data->sky.img || !data->floor.img)
		return (false);
	fill(data->sky);
	fill(data->floor);
	mlx_image_to_window(data->mlx, data->floor.img, 0, data->camy);
	mlx_image_to_window(data->mlx, data->sky.img, 0, 0);
	return (true);
}