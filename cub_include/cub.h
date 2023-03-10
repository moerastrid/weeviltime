/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 21:07:07 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "cub_setup.h"
# include "cub_structs.h"
# include "get_next_line.h"
# include "line.h"

// debug
//void			print_integer_map(t_data *data);

// graphics
void			exit_hook(void *param);
void			turn_hook(t_data *data);
void			forward_move_hook(t_data *data, t_coll *coll);
void			back_move_hook(t_data *data, t_coll *coll);
void			right_move_hook(t_data *data, t_coll *coll);
void			left_move_hook(t_data *data, t_coll *coll);
void			get_direction(t_data *data, t_ray *ray, float angle, int n);
void			gameloop(void *param);
int				graphics(t_data *data);
void			draw_nose(t_data *data);
void			draw_rays(t_data	*data);
void			fill_background(t_data *data);
void			fill_square(t_img *img, int height, int width, unsigned int c);
void			ft_fill(t_img *img, mlx_t *mlx, unsigned int color);
void			ft_line(t_img *img, t_line *line, unsigned int color);
void			make_one_ray(t_data *data, float a, int n, t_ray *ray_final);
void			draw_wall_line(t_data *data, t_ray *ray, float a, float dist);
void			draw_one_ray(t_data *data, t_ray *ray, unsigned int color);

// parse
int				check_map(t_data *data, t_par *par);
int				get_data(t_data *data, t_par *par);
int				get_elem(t_data *data, t_par *par, char *line);
int				get_map(t_data *data, t_par *par, char *line);
int				parse(int argc, char **argv, t_data *data);
int				set_map(t_data *data, t_par *par);

// raycasting
float			deg_to_rad(float a);
float			fix_ang(float a);

// utils
void			free_array(char **array);
void			free_par(t_par *par);
void			free_data(t_data	*data);
char			*get_next_line(int fd);
bool			stringisdigit(char *s);
char			**ft_single_split(char const *s, char c);
unsigned int	make_color(int r, int g, int b);
int				print_error(char *s, int retval);
void			putpixel(t_img *i, uint32_t x, uint32_t y, uint32_t c);
char			*trim_newline(char *s);

#endif