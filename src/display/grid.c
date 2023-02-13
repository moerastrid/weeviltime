/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:07:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/13 14:28:57 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	draw_height(mlx_image_t *grid, int x, float height, double color)
{
	int			i;

	i = 0;
	while (i < height)
	{
		wrap_putpixel(grid, x, (HEIGHT/2) + i, color);
		wrap_putpixel(grid, x, (HEIGHT/2) - i, color);
		i++;
	}
	i = 0;
	while (i > height)
	{
		wrap_putpixel(grid, x, (HEIGHT/2) + i, color);
		wrap_putpixel(grid, x, (HEIGHT/2) - i, color);
		i--;
	}
}

int	wavy_height(int x)
{
	int	height;

	height = 0;
	height = sin((3.14/150) * x);
	if (height < 0)
		height = height * 1;
	printf("heigth: %d\n", height);
	return (height);
}

float	calculate_height(t_data *data, int x)
{
	float	height;
	float	angle;
	//int		player_x;
	//int		player_y;
	//int		wall_x;
	//int		wall_y;
	float	distance_to_wall;

	(void)data;
	distance_to_wall = 2.5;
	angle = (3.14 / WIDTH) * x;
	printf("angle: %f\n", angle);
	height = ((HEIGHT * 2) / 8) + (20 * distance_to_wall * sin(angle));
	printf("height: %f\n", height);
	return (height);
}

bool	grid(t_data *data)
{
	mlx_image_t	*grid;
	int			x;
	float		height;

	grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!grid)
		return (false);
	x = 0;
	height = 0;
	while (x < WIDTH)
	{
		//height = wavy_height(x);
		//draw_height(grid, x, height, 0xF0A84CFF);
		height = calculate_height(data, x);
		draw_height(grid, x, height, 0x0E345BFF);
		x++;
	}
	mlx_image_to_window(data->mlx, grid, 0, 0);
	return (true);
}
