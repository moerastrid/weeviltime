/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:07:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/06 17:18:37 by ageels        ########   odam.nl         */
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

void	draw_cross(mlx_image_t	*grid)
{
	t_co	upleft;
	t_co	upright;
	t_co	downleft;
	t_co	downright;

	upleft.x = 0;
	upleft.y = 0;
	upright.x = WIDTH;
	upright.y = 0;
	downleft.x = 0;
	downleft.y = HEIGHT;
	downright.x = WIDTH;
	downright.y = HEIGHT;
	line(grid, &upleft, &downright);
	line(grid, &upright, &downleft);
}

void	grid(t_data *data)
{
	mlx_image_t		*grid;
	t_co	c;

	grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	draw_cross(grid);
	c.x = 200;
	c.y = 100;
	draw_cube(grid, c);
	mlx_image_to_window(data->mlx, grid, 0, 0);
}
