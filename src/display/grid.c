/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 16:07:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 19:23:25 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	create_empty_line(t_line *testline, int ax, int ay, int bx, int by)
{
	testline->ax = ax;
	testline->ay = ay;
	testline->bx = bx;
	testline->by = by;
	testline->dx = 0;
	testline->dy = 0;
	testline->slope = 0;
	testline->contactpoint = 0;
	testline->color = 0xFFFFFFFF;
}

static void	draw_enc(mlx_image_t *grid, t_line dl_one, t_line dl_two, int y)
{
	t_line		encounter;	

	create_empty_line(&encounter, 0, 0, 0, 0);
	encounter.ay = y;
	encounter.ax = (y - dl_one.contactpoint) / dl_one.slope;
	encounter.by = y;
	encounter.bx = (y - dl_two.contactpoint) / dl_two.slope;
	line(grid, &encounter);
}

static void	diagonals(mlx_image_t *grid, uint32_t color)
{
	float		magic_no_one = 200;
	float		magic_no_two = 280;
	float		magic_no_three = 30;
	t_line		dl_one;
	t_line		dl_two;

	create_empty_line(&dl_one, 0, magic_no_one, WIDTH, HEIGHT - magic_no_one);
	dl_one.color = color;
	line(grid, &dl_one);
	create_empty_line(&dl_two, WIDTH, magic_no_one, 0, HEIGHT - magic_no_one);
	dl_two.color = color;
	line(grid, &dl_two);
	draw_enc(grid, dl_one, dl_two, magic_no_one);
	draw_enc(grid, dl_one, dl_two, magic_no_two);
	draw_enc(grid, dl_one, dl_two, magic_no_three);
	draw_enc(grid, dl_one, dl_two, HEIGHT - magic_no_one);
	draw_enc(grid, dl_one, dl_two, HEIGHT - magic_no_two);
	draw_enc(grid, dl_one, dl_two, HEIGHT - magic_no_three);
	create_empty_line(&dl_one, ((magic_no_two /HEIGHT)*WIDTH), 0, WIDTH - ((magic_no_two /HEIGHT)*WIDTH), HEIGHT);
	dl_one.color = color;
	line(grid, &dl_one);
	create_empty_line(&dl_two, WIDTH - ((magic_no_two /HEIGHT)*WIDTH), 0, ((magic_no_two /HEIGHT)*WIDTH), HEIGHT);
	dl_two.color = color;
	line(grid, &dl_two);
	create_empty_line(&dl_one, ((magic_no_three /HEIGHT)*WIDTH), 0, WIDTH - ((magic_no_three /HEIGHT)*WIDTH), HEIGHT);
	dl_one.color = color;
	line(grid, &dl_one);
	create_empty_line(&dl_two, WIDTH - ((magic_no_three /HEIGHT)*WIDTH), 0, ((magic_no_three /HEIGHT)*WIDTH), HEIGHT);
	dl_two.color = color;
	line(grid, &dl_two);
}

void	grid(t_data *data)
{
	mlx_image_t	*grid;

	grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	diagonals(grid, 0xF3BFB3FF);
	mlx_image_to_window(data->mlx, grid, 0, 0);
}
