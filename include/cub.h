/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
<<<<<<< HEAD:include/header.h
/*   Updated: 2023/02/19 22:16:38 by astrid        ########   odam.nl         */
=======
/*   Updated: 2023/02/16 21:44:19 by ageels        ########   odam.nl         */
>>>>>>> main:include/cub.h
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "./cub_structs.h"
# include "./get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// temporary!
# define WIDTH 720
# define HEIGHT 720
# define FOV 1.256

<<<<<<< HEAD:include/header.h
# define NO	0
# define SO	1
# define WE	2
# define EA	3
# define C 0
# define F 1

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
}	t_player;

typedef struct s_plane
{
	mlx_image_t		*img;
	unsigned int	color;
}	t_plane;

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
	mlx_t			*mlx;
	t_wall			walls;
	mlx_image_t		*wall;
	t_plane			ceiling;
	t_plane			floor;
	t_co			cam;
	t_list			*map_lines;
	char			**map_array;
	int				map_y;
	t_player		player;
	float			distance_to_wall;	// Milan aan t testen
	bool			*wall_check;
	bool			*color_check;
// 	t_wall			wall;
}	t_data;

=======
>>>>>>> main:include/cub.h
//DEBUG
void			print_map(t_data *data);

//DISPLAY
bool			display(t_data *data);
bool			display_background(t_data *data);
bool			display_blokje(t_data *data);
bool			display_walls(t_data *data);

//PARSE
int				check_map(t_data *data);
int				check_player_spawn(t_data *data);
int				convert_map(t_data *data, t_par *pars);
int				init_map(t_data *data, t_par *pars);
bool			init_plane(t_data *data, char *line, t_par *pars);
bool			init_walls(t_data *data, char *line, t_par *pars);
int				save_map(int map, t_data *data, char *line);
int				setup(int argc, char **argv, t_data *data);

//UTILS
// clean
void			clean_everything(t_data *data);
//math
float			calculate_distance(void);
float			calculate_height(t_data *data, int x);
//single alloc split
char			**ft_single_split(char const *s, char c);
//wraps
int				print_error(char *s);
unsigned int	make_color(int r, int g, int b);
void			wrap_putpixel(mlx_image_t *img, uint32_t x, uint32_t y,
					uint32_t color);

#endif
