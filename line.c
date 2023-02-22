/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 18:18:27 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/22 12:46:35 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"
#include "line.h"

t_line	set_line_coords(int xa, int ya, int xb, int yb)
{
	t_line	line;

	line.xa = xa;
	line.ya = ya;
	line.xb = xb;
	line.yb = yb;
	return (line);
}

void	ft_pixelputwrap(t_img *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

void	updownleftright(t_img *img, t_line *line, float mn[2], uint32_t color)
{
	while (line->ya <= line->yb && line->xa <= line->xb)
	{
		ft_pixelputwrap(img, line->xa, line->ya, color);
		if (line->ya <= (mn[0] * line->xa) + mn[1]
			&& (line->ya + 1) >= (mn[0] * line->xa) + mn[1])
			line->xa++;
		else
			line->ya++;
	}
	return ;
}

void	downupleftright(t_img *img, t_line *line, float mn[2], uint32_t color)
{
	while (line->ya >= line->yb && line->xa <= line->xb)
	{
		ft_pixelputwrap(img, line->xa, line->ya, color);
		if (line->ya <= (mn[0] * line->xa) + mn[1]
			&& (line->ya + 1) > (mn[0] * line->xa + mn[1]))
			line->xa++;
		else
			line->ya--;
	}
}

void	updownrightleft(t_img *img, t_line *line, float mn[2], uint32_t color)
{
	while (line->ya <= line->yb && line->xa >= line->xb)
	{
		ft_pixelputwrap(img, line->xa, line->ya, color);
		if (line->ya >= (mn[0] * line->xa) + mn[1]
			&& (line->ya - 1) <= (mn[0] * line->xa) + mn[1])
			line->xa--;
		else
			line->ya++;
	}
}

void	downuprightleft(t_img *img, t_line *line, float mn[2], uint32_t color)
{
	while (line->ya >= line->yb && line->xa >= line->xb)
	{
		ft_pixelputwrap(img, line->xa, line->ya, color);
		if (line->ya >= (mn[0] * line->xa) + mn[1]
			&& (line->ya - 1) <= (mn[0] * line->xa + mn[1]))
			line->xa--;
		else
			line->ya--;
	}
}

void	ft_line(t_img *img, t_line *line, uint32_t color)
{
	float		xd;
	float		yd;
	float		mn[2];

	xd = line->xb - line->xa;
	yd = line->yb - line->ya;
	mn[0] = yd / xd;
	mn[1] = line->ya - (line->xa * mn[0]);
	if (line->ya <= line->yb && line->xa <= line->xb)
		updownleftright(img, line, mn, color);
	else if (line->ya >= line->yb && line->xa <= line->xb)
		downupleftright(img, line, mn, color);
	else if (line->ya <= line->yb && line->xa >= line->xb)
		updownrightleft(img, line, mn, color);
	else if (line->ya >= line->yb && line->xa >= line->xb)
		downuprightleft(img, line, mn, color);
	return ;
}
