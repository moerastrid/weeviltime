/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:07:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 16:35:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	empty_line(t_line *testline)
{
	testline->ax = 0;
	testline->ay = 0;
	testline->bx = 0;
	testline->by = 0;
	testline->dx = 0;
	testline->dy = 0;
	testline->slope = 0;
	testline->contactpoint = 0;
	testline->color = 0x000000FF;
}

static void	diagonals(mlx_image_t *grid, uint32_t color)
{
	t_line		dl_one;
	t_line		dl_two;

	empty_line(&dl_one);
	dl_one.ax = 0;
	dl_one.ay = 0;
	dl_one.bx = WIDTH;
	dl_one.by = HEIGHT;
	dl_one.color = color;
	line(grid, &dl_one);
	empty_line(&dl_two);
	dl_two.ax = WIDTH;
	dl_two.ay = 0;
	dl_two.bx = 0;
	dl_two.by = HEIGHT;
	dl_two.color = color;
	line(grid, &dl_two);
}

void	grid(t_data *data)
{
	mlx_image_t	*grid;

	grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	diagonals(grid, 0xFCEDDAFF);
	mlx_image_to_window(data->mlx, grid, 0, 0);
}
