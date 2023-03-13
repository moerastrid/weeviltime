/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wraps.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:08:40 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 16:19:17 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

unsigned int	make_color(int r, int g, int b)
{
	return ((unsigned int)(r << 24 | g << 16 | b << 8 | 0xFF));
}

int	print_error(char *s, int retval)
{
	printf("Error\n%s\n", s);
	return (retval);
}

void	putpixel(t_img *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height && x > 0 && y > 0)
		mlx_put_pixel(img, x, y, color);
}

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

float	fix_ang(float a)
{
	if (a > 359.0)
		a -= 360.0;
	if (a < 0)
		a += 360.0;
	return (a);
}
