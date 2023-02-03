/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:07:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 16:16:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	empty_line(t_line *testline)
{
	testline->ax = 0;
	testline->ay = 0;
	testline->bx = 0;
	testline->by = 0;
	testline->dx = 0;
	testline->dy = 0;
	testline->slope = 0;
	testline->contactpoint = 0;
	testline->color = 0xFFFFFFFF;
}

void	grid(t_data *data)
{
	mlx_image_t	*grid;
	t_line		testline;

	grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	empty_line(&testline);
	testline.ax = 0;
	testline.ay = 0;
	testline.bx = WIDTH;
	testline.by = HEIGHT;
	line(grid, &testline);
	mlx_image_to_window(data->mlx, grid, 0, 0);
}
