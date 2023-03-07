/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 12:44:50 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/07 16:53:19 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H
# include "cub.h"

typedef mlx_image_t	t_img;

typedef struct s_line
{
	int	xa;
	int	ya;
	int	xb;
	int	yb;
}	t_line;

void	ft_line(t_img *img, t_line *line, uint32_t color);

#endif