/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 12:44:50 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/28 17:53:57 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H
# include "cub_include/cub.h"

typedef mlx_image_t	t_img;

typedef struct s_line
{
	int		xa;
	int		ya;
	int		xb;
	int		yb;
}	t_line;

t_line	set_line_coords(int xa, int ya, int xb, int yb);
void	ft_pixelputwrap(t_img *img, uint32_t x, uint32_t y, uint32_t color);
void	ft_line(t_img *img, t_line *line, uint32_t color);

#endif