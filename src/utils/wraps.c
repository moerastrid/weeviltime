/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wraps.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:08:40 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 16:09:24 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	wrap_putpixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}
