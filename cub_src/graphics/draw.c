/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 22:02:35 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/03 22:21:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	fill_square(t_img *img, int height, int width, unsigned int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			putpixel(img, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_nose(t_data *data)
{
	int			height;
	t_player	*p;
	t_line		nose;

	p = &data->player;
	height = data->mms / 4;
	nose.xa = p->x * data->mms + height * 2;
	nose.ya = p->y * data->mms + height * 2;
	nose.xb = p->x * data->mms + height * 2 + cos(deg_to_rad(p->direction)) * 25;
	nose.yb = p->y * data->mms + height * 2 - sin(deg_to_rad(p->direction)) * 25;
	ft_line(data->background, &nose, 0xF0F0F0FF);
}

static void	fill_background(t_data *data)
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
				putpixel(data->background, i, j, data->planes[C]);
			else
				putpixel(data->background, i, j, data->planes[F]);
			i++;
		}
		j++;
	}
}

void	draw_world(t_data *data)
{
	fill_background(data);
}
