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

static void	updownleftright(mlx_image_t *img, t_line *l)
{
	while (l->ay <= l->by && l->ax <= l->bx)
	{
		wrap_putpixel(img, l->ax, l->ay, l->color);
		if (l->ay <= (l->slope * l->ax) + l->contactpoint
			&& (l->ay + 1) >= (l->slope * l->ax) + l->contactpoint)
			l->ax++;
		else
			l->ay++;
	}
	return ;
}

static void	downupleftright(mlx_image_t *img, t_line *l)
{
	while (l->ay >= l->by && l->ax <= l->bx)
	{
		wrap_putpixel(img, l->ax, l->ay, l->color);
		if (l->ay <= (l->slope * l->ax) + l->contactpoint
			&& (l->ay + 1) > (l->slope * l->ax + l->contactpoint))
			l->ax++;
		else
			l->ay--;
	}
}

static void	updownrightleft(mlx_image_t *img, t_line *l)
{
	while (l->ay <= l->by && l->ax >= l->bx)
	{
		wrap_putpixel(img, l->ax, l->ay, l->color);
		if (l->ay >= (l->slope * l->ax) + l->contactpoint
			&& (l->ay - 1) <= (l->slope * l->ax) + l->contactpoint)
			l->ax--;
		else
			l->ay++;
	}
}

static void	downuprightleft(mlx_image_t *img, t_line *l)
{
	while (l->ay >= l->by && l->ax >= l->bx)
	{
		wrap_putpixel(img, l->ax, l->ay, l->color);
		if (l->ay >= (l->slope * l->ax) + l->contactpoint
			&& (l->ay - 1) <= (l->slope * l->ax + l->contactpoint))
			l->ax--;
		else
			l->ay--;
	}
}

void	line(mlx_image_t *img, t_line *l)
{
	l->dx = l->bx - l->ax;
	l->dy = l->by - l->ay;
	l->slope = l->dy / l->dx;
	l->contactpoint = l->ay - (l->ax * l->slope);
	if (l->ay <= l->by && l->ax <= l->bx)
		updownleftright(img, l);
	else if (l->ay >= l->by && l->ax <= l->bx)
		downupleftright(img, l);
	else if (l->ay <= l->by && l->ax >= l->bx)
		updownrightleft(img, l);
	else if (l->ay >= l->by && l->ax >= l->bx)
		downuprightleft(img, l);
	return ;
}
