/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:07:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/08 21:00:53 by astrid        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	draw_height(mlx_image_t *grid, int x, int height, double color)
{
	int			i;

	i = 0;
	while (i < height)
	{
		wrap_putpixel(grid, x, (HEIGHT/2) + i, color);
		wrap_putpixel(grid, x, (HEIGHT/2) - i, color);
		i++;
	}
}

int	wavy_height(int x)
{
	int	height;

	height = 0;
	height = sin(3.14 * 15 * x) * 150;
	return (height);
}

int	calculate_height(t_data *data, int x)
{
	int height;

	(void)x;
	(void)data;
	height = x % (WIDTH / 20);
	return (height);
}

bool	grid(t_data *data)
{
	mlx_image_t		*grid;
	int				x;
	int				height;

	grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!grid)
		return(false);
	x = 0;
	height = 0;
	while (x  < WIDTH)
	{
		height = wavy_height(x);
		draw_height(grid, x, height, 0xF0A84CFF);
		height = calculate_height(data, x);
		draw_height(grid, x, height, 0x0E345BFF);
		x++;
	}
	mlx_image_to_window(data->mlx, grid, 0, 0);
	return(true);
}
