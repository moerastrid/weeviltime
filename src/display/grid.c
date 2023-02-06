/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:07:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/06 16:30:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	grid(t_data *data)
{
	mlx_image_t	*grid;
	t_cube		c;
	int			i;

	grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	c.x = 100;
	c.y = 100;
	c.length = 40;
	i = 0;
	while (i < c.length)
	{
		wrap_putpixel(grid, c.x, c.y + 1, 0xFFFFFFFF);
		i++;
	}
	mlx_image_to_window(data->mlx, grid, 0, 0);
}
