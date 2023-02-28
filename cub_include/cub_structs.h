/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 20:36:31 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 17:45:58 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

# ifndef WIDTH
#  define WIDTH 400
# endif
# ifndef HEIGHT
#  define HEIGHT 400
# endif
# ifndef mapS
#  define mapS 16
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
	int			x;
	int			y;
}		t_co;

/*	plane: floor or ceiling	*/
typedef struct s_plane
{
	//mlx_image_t		*img;
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
	float	direction;
	t_co	pos;
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

/*	general data	*/
typedef struct s_data
{
	mlx_t		*mlx;
	t_co		max;
	t_par		*par;
	t_plane		*planes;
	t_player	player;
	t_wall		*walls;
}		t_data;

#endif