/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 18:19:35 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <math.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "./cub_structs.h"
# include "./get_next_line.h"
# include "./line.h"

// debug
void			print_map(t_par *par);

// graphics
// :)

// parse
int				check_map(t_data *data, t_par *par);
int				compatibalize_map(t_data *data, t_par *par);
int				get_data(t_data *data, t_par *par);
int				get_elem(t_data *data, t_par *par, char *line);
int				get_map(t_data *data, t_par *par, char *line);
int				parse(int argc, char **argv, t_data *data);
int				get_map(t_data *data, t_par *par, char *line);

// raycasting
void			init_raydata(t_data *data, t_rays *rays);
void			init_textures(t_data *data);
void			draw_player(t_data *data);
void			drawMap2D(t_data *data);
void			input_hook(mlx_key_data_t keydata, void *param);
void			hook(void *param);

// utils
void			free_array(char **array);
void			free_par(t_par *par);
void			free_data(t_data	*data);
char			*get_next_line(int fd);
bool			stringisdigit(char *s);
char			**ft_single_split(char const *s, char c);
unsigned int	make_color(int r, int g, int b);
int				print_error(char *s);
void			putpixel(mlx_image_t *i, uint32_t x, uint32_t y, uint32_t c);

#endif