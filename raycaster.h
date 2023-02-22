/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 15:32:25 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/22 15:34:35 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "include/cub.h"
# include "line.h"

typedef struct s_raymath
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	disv;
	float	dish;
}	t_raymath;

typedef struct s_raydata
{
	mlx_t		*mlx;
	t_raymath	r_math;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*grid;
	mlx_image_t	*floor;
	t_line		line;
	bool		display_rays;
	float		pdx;
	float		pdy;
	float		pa;
}	t_raydata;

#endif