/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/13 14:44:49 by mforstho      ########   odam.nl         */
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
# include <math.h>
# include "../libft/libft.h"
# include "../src/get_next_line/get_next_line.h"

# define SKYCOLOR	0xB9D2D6FF
# define FLOORCOLOR	0xEBBAB9FF

# define WIDTH 720
# define HEIGHT 720

# define FOV 1.256

//# define NO	0
//# define SO	1
//# define WE	2
//# define EA	3

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
}	t_player;

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

// type coordinate: (with z as length because otherwise it's confusing.)
typedef struct s_co
{
	float	x;
	float	length;
}		t_co;

typedef struct s_point
{
	char	s;
	int		x;
	int		y;
}	t_point;

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
	t_list			*map_lines;
	char			**map_array;
	int				map_size;
	t_player		player;
	float			distance_to_wall;	// Milan aan t testen
// 	t_wall			wall;
}	t_data;

//display
bool			display(t_data *data);
bool			background(t_data *data);
bool			build(t_data *data);
bool			grid(t_data *data);

//parse
int				parse(int argc, char **argv, t_data *data);
int				init_map_data(int map, t_data *data);

//check_map
int				check_map_spaces(t_data *data);
int				check_map_tabs(t_data *data);

//player
int				get_player_spawn(t_data *data);

//print_map
void			print_map(t_data *data);

//save_and_convert_map
int				convert_map(t_data *data);
int				save_map(int map, t_data *data, char *line);

//utils
void			wrap_putpixel(mlx_image_t *img, uint32_t x, uint32_t y,
					uint32_t color);
unsigned int	make_color(int r, int g, int b);

#endif
