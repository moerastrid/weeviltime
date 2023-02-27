/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 14:15:35 by ageels        ########   odam.nl         */
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

// parse
bool			get_elem(t_data *data, t_par *par, char *temp_line);
int				get_data(t_data *data, t_par *par);
int				parse(int argc, char **argv, t_data *data);

// utils
char			*get_next_line(int fd);
bool			stringisdigit(char *s);
char			**ft_single_split(char const *s, char c);
unsigned int	make_color(int r, int g, int b);
int				print_error(char *s);
void			putpixel(mlx_image_t *i, uint32_t x, uint32_t y, uint32_t c);

#endif
