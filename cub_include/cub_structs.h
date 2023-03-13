/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 20:36:31 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 16:54:12 by ageels        ########   odam.nl         */
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
	char			*path;
	mlx_texture_t	*texture;
}		t_wall;

/* player data */
typedef struct s_player
{
	float			x;
	float			y;
	float			dirx;
	float			diry;
	float			lrx;
	float			lry;
	float			angle;
	t_img			*image;
}		t_player;

/*	ray data	*/
typedef struct s_ray
{
	int		no;
	t_line	line;
	t_co	dir;
	float	ax;
	float	ay;
	float	bx;
	float	by;
	int		side;
}		t_ray;

/*	parse data	*/
typedef struct s_par
{
	bool		*wall_check;
	bool		*color_check;
	char		**maparray;
	int			fd_cub;
	int			p_count;
	t_list		*maplst;
}		t_par;

/*	collision	*/
typedef struct s_coll
{
	float	ipx;
	float	ipy;
	float	ipx_add_xo;
	float	ipx_sub_xo;
	float	ipy_add_yo;
	float	ipy_sub_yo;
}	t_coll;

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
	t_img			*world;
	t_coll			collision;
}		t_data;

#endif
