/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 16:24:28 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/03 17:46:28 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

t_line	set_line_coords(int xa, int ya, int xb, int yb)
{
	t_line	line;

	line.xa = xa;
	line.ya = ya;
	line.xb = xb;
	line.yb = yb;
	return (line);
}

static void	fill_square(t_img *img, int height, int width, unsigned int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			putpixel(img, i, j, color);
			i++;
		}
		j++;
	}
}

static int	draw_player(t_data *data)
{
	int			height;
	t_player	p;
	t_line		nose;

	p = data->player;
	height = MMS / 4;
	p.self = mlx_new_image(data->mlx, height, height);
	if (!p.self)
		return (print_error("MLX error"));
	p.grid = mlx_new_image(data->mlx, data->max.x * MMS, data->max.y *MMS);
	if (!p.grid)
		return (print_error("MLX error"));
	fill_square(p.self, height, height, 0xF0F0F0FF);
	nose.xa = p.x * MMS + height * 2;
	nose.ya = p.y * MMS + height * 2;
	nose.xb = p.x * MMS + height * 2 + cos(deg_to_rad(p.direction)) * 25;
	nose.yb = p.y * MMS + height * 2 - sin(deg_to_rad(p.direction)) * 25;
	printf("nose: %d %d %d %d\n", nose.xa, nose.xb, nose.ya, nose.yb);
	ft_line(p.grid, &nose, 0xF0F0F0FF);
	mlx_image_to_window(data->mlx, p.self, \
		p.x * MMS + height * 1.5, p.y * MMS + height * 1.5);
	mlx_image_to_window(data->mlx, p.grid, 0, 0);
	return (EXIT_SUCCESS);
}

int	draw_minimap(t_data *data)
{
	int		x;
	int		y;
	t_img	*tile;

	tile = mlx_new_image(data->mlx, MMS - 1, MMS - 1);
	if (!tile)
		return (print_error("MLX error"));
	fill_square(tile, MMS - 1, MMS - 1, data->planes[F] / 2);
	y = 0;
	while (y < data->max.y)
	{
		x = 0;
		while (x < data->max.x)
		{
			if (data->map[y * data->max.x + x] == 1)
				mlx_image_to_window(data->mlx, tile, x * MMS, y * MMS);
			x++;
		}
		y++;
	}
	if (draw_player(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
