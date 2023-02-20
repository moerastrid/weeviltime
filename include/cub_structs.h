/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 20:36:31 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/20 14:37:57 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

typedef enum e_wall_side
{
	NO,
	SO,
	WE,
	EA,
}	t_wall_side;

typedef enum e_plane
{
	C,
	F,
}	t_planes;	// betere naam geven om verwarring te voorkomen

// direction in rad please :) 
// NO = 0 rad, SO = pi rad, EA = 0,5pi rad, WE = 1,5pi rad
typedef struct s_player
{
	float	x;
	float	y;
	float	direction;
}	t_player;

typedef struct s_plane
{
	mlx_image_t		*img;
	unsigned int	color;
}	t_plane;

typedef struct s_wall
{
	mlx_image_t	*wall_north;
	mlx_image_t	*wall_south;
	mlx_image_t	*wall_east;
	mlx_image_t	*wall_west;
}	t_wall;

typedef struct s_co
{
	float	x;
	float	y;
}		t_co;

typedef struct s_data
{
	int				map_y;
	char			**map_array;
	mlx_t			*mlx;
	mlx_image_t		*wall;
	t_wall			walls;
	t_plane			ceiling;
	t_plane			floor;
	t_co			cam;
	t_list			*map_lines;
	bool			*wall_check;
	bool			*color_check;
	t_player		player;
}	t_data;

#endif