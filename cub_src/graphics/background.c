/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:48:59 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 21:53:05 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	display_background(t_img *img, t_data *data)
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
				putpixel(img, i, j, data->planes[C].color);
			else
				putpixel(img, i, j, data->planes[F].color);
			i++;
		}
		j++;
	}
}
