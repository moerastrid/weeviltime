/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/22 18:03:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "./cub_structs.h"
# include "./get_next_line.h"

// utils
char			*get_next_line(int fd);
char			**ft_single_split(char const *s, char c);
unsigned int	make_color(int r, int g, int b);
int				print_error(char *s);
void			wrap_putpixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);

#endif
