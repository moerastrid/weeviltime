/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 16:42:39 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <memory.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../src/get_next_line/get_next_line.h"

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
}	t_skyfl;

typedef struct s_wall
{
	mlx_image_t		*wall_north;
	mlx_image_t		*wall_south;
	mlx_image_t		*wall_east;
	mlx_image_t		*wall_west;
}	t_wall;

typedef struct s_line
{
	int				ax;
	int				ay;
	int				bx;
	int				by;
	float			dx;
	float			dy;
	float			slope;
	float			contactpoint;
	unsigned int	color;
}		t_line;

typedef struct s_data
{
	mlx_t			*mlx;
	t_wall			walls;
	mlx_image_t		*wall;
	t_skyfl			sky;
	t_skyfl			floor;
	float			camx;
	float			camy;
	char			**wall_textures;
	char			**f_c_color;
//	t_player		player;
// 	t_wall			wall;
// 	t_list			*map_lines;
//	char			**map_array;
}	t_data;

//display
bool	background(t_data *data);
bool	display(t_data *data);
bool	build(t_data *data);
void	grid(t_data *data);
void	line(mlx_image_t *img, t_line *l);
unsigned int	make_color(int r, int g, int b);
//parse
int		parse(int argc, char **argv, t_data *data);
int		init_map_data(int map, t_data *data);
//utils
void	wrap_putpixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
#endif