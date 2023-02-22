/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wraps.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:08:40 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/22 18:00:06 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

unsigned int	make_color(int r, int g, int b)
{
	return ((unsigned int)(r << 24 | g << 16 | b << 8 | 0xFF));
}

int	print_error(char *s)
{
	printf("%s\n", s);
	return (EXIT_FAILURE);
}

void	wrap_putpixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}
