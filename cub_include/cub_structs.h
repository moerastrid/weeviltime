/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 20:36:31 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/08 14:52:37 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

# include "cub.h"
# include "line.h"

typedef mlx_image_t	t_img;

/*	wall side parameters	*/
typedef enum e_wall_side
{
	NO,
	SO,
	WE,
	EA,
}		t_wall_e;

/*	C: ceiling
	F: floor	*/
typedef enum e_eplane
{
	C,
	F,
}		t_plane_e;

/*	coordinate	*/
typedef struct s_co
{
	int		x;
	int		y;
}		t_co;

/*	wall: NO, SO, WE or EA	*/
typedef struct s_wall
{
	//t_img		*img;
	char		*path;
}		t_wall;

/* player data */
typedef struct s_player
{
	float			x;
	float			y;
	float			dirx;
	float			diry;
	float			angle;
	t_img			*image;
	//mlx_instance_t	*instance;
}		t_player;

/*	ray data	*/
typedef struct s_ray
{
	t_line	line;
	t_co	dir;
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
}		t_ray;

/*	parse data	*/
typedef struct s_par
{
	bool		*wall_check;
	bool		*color_check;
	char		**maparray;
	int			fd_cub;
	t_list		*maplst;
}		t_par;

/*	general data	*/
typedef struct s_data
{
	mlx_t			*mlx;
	t_co			max;
	int				**map;
	int				mms;
	unsigned int	*planes;
	t_player		player;
	t_wall			*walls;
	t_img			*background;
	t_img			*tile;
	t_img			*grid;
}		t_data;

#endif

///*	ray data	*/
//typedef struct s_raymath
//{
//	int		r;
//	int		mx;
//	int		my;
//	int		mp;
//	int		dof;
//	float	vx;
//	float	vy;
//	float	rx;
//	float	ry;
//	float	ra;
//	float	xo;
//	float	yo;
//	float	disv;
//	float	dish;
//}	t_raymath;

//typedef struct s_raydata
//{
//	t_raymath	r_math;
//	mlx_image_t	*player;
//	mlx_image_t	*wall;
//	mlx_image_t	*grid;
//	mlx_image_t	*floor;
//	t_line		line;
//	bool		display_rays;
//	float		pdx;
//	float		pdy;
//	float		ppddxx;
//	float		ppddyy;
//	float		pa;
//}	t_rays;

