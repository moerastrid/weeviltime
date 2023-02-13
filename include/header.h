/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/14 00:57:11 by ageels        ########   odam.nl         */
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
# include "./get_next_line.h"

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

typedef struct s_co
{
	float	x;
	float	y;
}		t_co;

typedef struct s_point
{
	char	s;
	int		x;
	int		y;
}	t_point;

typedef struct s_data
{
	mlx_t		*mlx;
	t_wall		walls;
	mlx_image_t	*wall;
	t_skyfl		sky;
	t_skyfl		floor;
	t_co		cam;
	t_co		map;
	char		**map_array;
	//char		**wall_textures;
	//t_list	*map_lines;
	//t_player	player;
	//float		distance_to_wall;	// Milan aan t testen
	//t_wall	wall;
}	t_data;

// F U N C T I O N S

//DEBUG
void			print_map(t_data *data);

//DISPLAY
bool			display(t_data *data);
bool			display_background(t_data *data);
bool			display_blokje(t_data *data);
bool			display_walls(t_data *data);

//PARSE
int				check_map(t_data *data);
int				parse(int argc, char **argv, t_data *data);
bool			set_data(int map_fd, t_data *data);
bool			set_map(t_data *data, char *line, int map_fd);
//int				get_player_spawn(t_data *data);
	// please rename this to "set player" for initilizing

//UTILS
//wraps
void			wrap_putpixel(mlx_image_t *img, \
					uint32_t x, uint32_t y, uint32_t color);
unsigned int	make_color(int r, int g, int b);
int				print_error(char *s);
//math
float			calculate_distance(void);
float			calculate_height(t_data *data, int x);
//single alloc split
char			**ft_single_split(char const *s, char c);

#endif
