/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:48:59 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/02 21:52:11 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	wrap_putpixel(mlx_image_t *img, uint32_t x, uint32_t y, unsigned int color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

unsigned int	make_color(int r, int g, int b)
{
	return ((unsigned int)(r << 24 | g << 16 | b << 8 | 0xFF));
}

void	fill(mlx_image_t *img, unsigned int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < img->height)
	{
		i = 0;
		while (i < img->width)
		{
			wrap_putpixel(img, i, j, color);
			i++;
		}
		j++;
	}
}

bool	background(t_data *data)
{
	mlx_image_t		*sky;
	mlx_image_t		*floor;

	sky = mlx_new_image(data->mlx, data->mlx->width, (data->mlx->height / 2));
	floor = mlx_new_image(data->mlx, data->mlx->width, (data->mlx->height / 2));
	if (!sky || !floor)
		return (false);
	fill(sky, SKYCOLOR);
	fill(floor, FLOORCOLOR);
	mlx_image_to_window(data->mlx, floor, 0, (data->mlx->height / 2));
	mlx_image_to_window(data->mlx, sky, 0, 0);
	return (true);
}
