/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:07:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/06 17:56:57 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	draw_cube(mlx_image_t *grid, t_co c)
{
	int			i;

	i = 0;
	c.length = HEIGHT - (2 * c.y);
	while (i < c.length)
	{
		wrap_putpixel(grid, c.x, c.y + i, 0xFF00FFFF);
		i++;
	}
}

void	draw_cross(mlx_image_t	*grid, int var_x, int var_y)
{
	t_co	upleft;
	t_co	upright;
	t_co	downleft;
	t_co	downright;

	upleft.x = var_x;
	upleft.y = var_y;
	upright.x = WIDTH - var_x;
	upright.y = var_y;
	downleft.x = var_x;
	downleft.y = HEIGHT - var_y;
	downright.x = WIDTH - var_x;
	downright.y = HEIGHT - var_y;
	line(grid, &upleft, &downright);
	line(grid, &upright, &downleft);
}

void	grid(t_data *data)
{
	mlx_image_t		*grid;
	t_co	c;

	grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	draw_cross(grid, 0, 0);
	draw_cross(grid, 0, 200);
	draw_cross(grid, 300, 0);
	c.x = 200;
	c.y = 100;
	draw_cube(grid, c);
	c.x = 300;
	c.y = 300;
	draw_cube(grid, c);
	mlx_image_to_window(data->mlx, grid, 0, 0);
}
