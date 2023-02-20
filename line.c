/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 18:18:27 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/20 17:56:15 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

typedef mlx_image_t	t_img;

typedef struct s_map
{
	t_img	*img;
	mlx_t	*mlx;
	char	*path;
	int		hor;
	int		ver;
	int		xa;
	int		xb;
	int		ya;
	int		yb;
	int		offsetx;
	int		offsety;
	int		zoom;
	int		steepness;
	float	angle;
}	t_map;

void	updownleftright(t_img *img, t_map *mapdata, float mn[2])
{
	while (mapdata->ya <= mapdata->yb && mapdata->xa <= mapdata->xb)
	{
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEEEEEEFF);
		if (mapdata->ya <= (mn[0] * mapdata->xa) + mn[1]
			&& (mapdata->ya + 1) >= (mn[0] * mapdata->xa) + mn[1])
			mapdata->xa++;
		else
			mapdata->ya++;
	}
	return ;
}

void	downupleftright(t_img *img, t_map *mapdata, float mn[2])
{
	while (mapdata->ya >= mapdata->yb && mapdata->xa <= mapdata->xb)
	{
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0x99EEEEFF);
		if (mapdata->ya <= (mn[0] * mapdata->xa) + mn[1]
			&& (mapdata->ya + 1) > (mn[0] * mapdata->xa + mn[1]))
			mapdata->xa++;
		else
			mapdata->ya--;
	}
}

void	updownrightleft(t_img *img, t_map *mapdata, float mn[2])
{
	while (mapdata->ya <= mapdata->yb && mapdata->xa >= mapdata->xb)
	{
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEE99EEFF);
		if (mapdata->ya >= (mn[0] * mapdata->xa) + mn[1]
			&& (mapdata->ya - 1) <= (mn[0] * mapdata->xa) + mn[1])
			mapdata->xa--;
		else
			mapdata->ya++;
	}
}

void	downuprightleft(t_img *img, t_map *mapdata, float mn[2])
{
	while (mapdata->ya >= mapdata->yb && mapdata->xa >= mapdata->xb)
	{
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEEEE99FF);
		if (mapdata->ya >= (mn[0] * mapdata->xa) + mn[1]
			&& (mapdata->ya - 1) <= (mn[0] * mapdata->xa + mn[1]))
			mapdata->xa--;
		else
			mapdata->ya--;
	}
}

void	ft_line(t_img *img, t_map *mapdata)
{
	float		xd;
	float		yd;
	float		mn[2];

	xd = mapdata->xb - mapdata->xa;
	yd = mapdata->yb - mapdata->ya;
	mn[0] = yd / xd;
	mn[1] = mapdata->ya - (mapdata->xa * mn[0]);
	if (mapdata->ya <= mapdata->yb && mapdata->xa <= mapdata->xb)
		updownleftright(img, mapdata, mn);
	else if (mapdata->ya >= mapdata->yb && mapdata->xa <= mapdata->xb)
		downupleftright(img, mapdata, mn);
	else if (mapdata->ya <= mapdata->yb && mapdata->xa >= mapdata->xb)
		updownrightleft(img, mapdata, mn);
	else if (mapdata->ya >= mapdata->yb && mapdata->xa >= mapdata->xb)
		downuprightleft(img, mapdata, mn);
	return ;
}
