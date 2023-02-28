/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 20:36:31 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 21:34:31 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

# include "cub.h"
# include "line.h"

# ifndef WIDTH
#  define WIDTH 2400
# endif
# ifndef HEIGHT
#  define HEIGHT 1200
# endif
# ifndef MMS
#  define MMS 16
# endif
# ifndef FOV
#  define FOV 70
# endif
# ifndef DOF
#  define DOF 32
# endif

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

/*	plane: floor or ceiling	*/
typedef struct s_plane
{
	mlx_image_t		*img;
	unsigned int	color;
}		t_plane;

/*	wall: NO, SO, WE or EA	*/
typedef struct s_wall
{
	//mlx_image_t		*img;
	char		*path;
}		t_wall;

/* player data */
typedef struct s_player
{
	int		x;
	int		y;
	float	pos_x;
	float	pos_y;
	float	direction;
}		t_player;

/*	parse data	*/
typedef struct s_par
{
	bool		*wall_check;
	bool		*color_check;
	char		**maparray;
	int			fd_cub;
	t_list		*maplst;
}		t_par;

/*	ray data	*/
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
}	t_rays;

/*	general data	*/
typedef struct s_data
{
	mlx_t		*mlx;
	t_rays		rays;
	t_co		max;
	int			*map;
	t_plane		*planes;
	t_player	player;
	t_wall		*walls;
}		t_data;

#endif