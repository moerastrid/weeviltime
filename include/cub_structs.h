/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 20:36:31 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/16 21:42:05 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

# define NO	0
# define SO	1
# define WE	2
# define EA	3
# define C 0
# define F 1

// direction in rad please :) 
// NO = 0 rad, SO = pi rad, EA = 0,5pi rad, WE = 1,5pi rad
typedef struct s_player
{
	int		x;
	int		y;
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

typedef struct s_parsing_data
{
	t_list	*map_lines;
	bool	*wall_check;
	bool	*color_check;
	int		fd;
}		t_par;

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
	t_player		player;
}	t_data;

#endif