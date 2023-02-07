/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   l.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 18:18:27 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 15:42:36 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	updownleftright(mlx_image_t *img, t_co *a, t_co *b, float cps[2])
{
	while (a->y <= b->y && a->x <= b->x)
	{
		wrap_putpixel(img, a->x, a->y, 0xFFFF00FF);
		if (a->y <= (cps[1] * a->x) + cps[0]
			&& (a->y + 1) >= (cps[1] * a->x) + cps[0])
			a->x++;
		else
			a->y++;
	}
	return ;
}

static void	downupleftright(mlx_image_t *img, t_co *a, t_co *b, float cps[2])
{
	while (a->y >= b->y && a->x <= b->x)
	{
		wrap_putpixel(img, a->x, a->y, 0xFFFF00FF);
		if (a->y <= (cps[1] * a->x) + cps[0]
			&& (a->y + 1) > (cps[1] * a->x + cps[0]))
			a->x++;
		else
			a->y--;
	}
}

static void	updownrightleft(mlx_image_t *img, t_co *a, t_co *b, float cps[2])
{
	while (a->y <= b->y && a->x >= b->x)
	{
		wrap_putpixel(img, a->x, a->y, 0xFFFF00FF);
		if (a->y >= (cps[1] * a->x) + cps[0]
			&& (a->y - 1) <= (cps[1] * a->x) + cps[0])
			a->x--;
		else
			a->y++;
	}
}

static void	downuprightleft(mlx_image_t *img, t_co *a, t_co *b, float cps[2])
{
	while (a->y >= b->y && a->x >= b->x)
	{
		wrap_putpixel(img, a->x, a->y, 0xFFFF00FF);
		if (a->y >= (cps[1] * a->x) + cps[0]
			&& (a->y - 1) <= (cps[1] * a->x + cps[0]))
			a->x--;
		else
			a->y--;
	}
}

// float cps[0]s stands for contact point (0) and cps[1] (1).
// to make the code norm, I put them together in an array.
void	line(mlx_image_t *img, t_co *a, t_co *b)
{
	float	cps[2];

	cps[1] = (b->y - a->y) / (b->x - a->x);
	cps[0] = a->y - (a->x * cps[1]);
	if (a->y <= b->y && a->x <= b->x)
		updownleftright(img, a, b, cps);
	else if (a->y >= b->y && a->x <= b->x)
		downupleftright(img, a, b, cps);
	else if (a->y <= b->y && a->x >= b->x)
		updownrightleft(img, a, b, cps);
	else if (a->y >= b->y && a->x >= b->x)
		downuprightleft(img, a, b, cps);
}
