/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:48:59 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/03 16:30:43 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static void	fill_background(t_img *img, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			if (j < HEIGHT / 2)
				putpixel(img, i, j, data->planes[C]);
			else
				putpixel(img, i, j, data->planes[F]);
			i++;
		}
		j++;
	}
}

int	draw_world(t_data *data)
{
	t_img	*background;

	background = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!background)
		return (print_error("MLX error"));
	fill_background(background, data);
	mlx_image_to_window(data->mlx, background, 0, 0);
	return (EXIT_SUCCESS);
}
