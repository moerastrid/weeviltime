/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:48:59 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/19 22:17:05 by astrid        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	fill(t_plane plane)
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

bool	display_background(t_data *data)
{
	data->ceiling.img = mlx_new_image(data->mlx, data->mlx->width, (data->mlx->height / 2));
	data->floor.img = mlx_new_image(data->mlx, data->mlx->width, (data->mlx->height / 2));
	if (!data->ceiling.img || !data->floor.img)
		return (false);
	fill(data->ceiling);
	fill(data->floor);
	mlx_image_to_window(data->mlx, data->floor.img, 0, data->cam.y);
	mlx_image_to_window(data->mlx, data->ceiling.img, 0, 0);
	return (true);
}
