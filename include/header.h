/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 13:49:57 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <memory.h>

# define SKYCOLOR	0xB9D2D6FF
# define FLOORCOLOR	0xEBBAB9FF

# define WIDTH 1024
# define HEIGHT 768

//# define NO	0
//# define SO	1
//# define WE	2
//# define EA	3

//typedef struct s_player
//{
//}	t_player;

typedef struct s_sky_or_floor
{
	mlx_image_t		*img;
	unsigned int	color;
}		t_skyfl;

//typedef struct s_wall
//{
//	mlx_image_t		*wall;
//}		t_wall;

typedef struct s_data
{
	mlx_t			*mlx;
	//t_wall			walls[4];
	mlx_image_t		*wall;
	t_skyfl			sky;
	t_skyfl			floor;
	int				camx;
	int				camy;
//	t_player		player;
// 	t_wall			wall;
// 	t_list			*map_lines;
//	char			**map_array;
}	t_data;

//display
bool	background(t_data *data);
bool	display(t_data *data);
bool	build(t_data *data);

//parse
int		parse(int argc, char **argv, t_data *data);

#endif