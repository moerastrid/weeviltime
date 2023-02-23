/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/23 13:57:38 by mforstho      ########   odam.nl         */
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
// # define FOV 1.256

void			free_array(char **arr);

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
int				convert_map(t_data *data);
// int				convert_map(t_data *data, t_par *pars);
int				init_map(int map, t_data *data);
// int				init_map(t_data *data, t_par *pars);
bool			init_plane(t_data *data, char *line);
// bool				init_plane(t_data *data, char *line, t_par *pars);
bool			init_wall(t_data *data, char *line);
// bool				init_walls(t_data *data, char *line, t_par *pars);
int				save_map(int map, t_data *data, char *line);
int				setup(int argc, char **argv, t_data *data);

//UTILS
// clean
void			clean_everything(t_data *data);
//math
//float			calculate_distance(void);
float			calculate_height(t_data *data, int x);
//single alloc split
char			**ft_single_split(char const *s, char c);
//wraps
int				print_error(char *s);
unsigned int	make_color(int r, int g, int b);
void			wrap_putpixel(mlx_image_t *img, uint32_t x, uint32_t y,
					uint32_t color);

#endif
