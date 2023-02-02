/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/02 22:01:59 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <memory.h>

#define SKYCOLOR 0xB9D2D6FF
#define FLOORCOLOR 0xEBBAB9FF

//typedef struct s_player
//{
//	mlx_instance_t	*instance;
//}	t_player;

typedef struct s_sky_or_floor
{
	mlx_image_t		*img;
	unsigned int	color;
}		t_skyfl;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*wall;
	t_skyfl		sky;
	t_skyfl		floor;
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