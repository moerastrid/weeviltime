/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 21:51:10 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/09 23:41:13 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static int	create_images(t_data *data)
{
	data->background = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->background)
		return (print_error("MLX error", EXIT_FAILURE));
	data->grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->grid)
		return (print_error("MLX error", EXIT_FAILURE));
	data->world = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->world)
		return (print_error("MLX error", EXIT_FAILURE));
	data->tile = mlx_new_image(data->mlx, data->mms - 1, data->mms - 1);
	if (!data->tile)
		return (print_error("MLX error", EXIT_FAILURE));
	data->player.image = mlx_new_image(data->mlx, data->mms / 4, data->mms / 4);
	if (!data->player.image)
		return (print_error("MLX error", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	display_minimap(t_data *data)
{
	int				x;
	int				y;

	fill_square(data->tile, data->mms - 1, data->mms - 1, data->planes[F] / 2);
	y = 0;
	while (y < data->max.y)
	{
		x = 0;
		while (x < data->max.x)
		{
			if (data->map[y][x] == 1)
			{
				if (mlx_image_to_window(data->mlx, data->tile, \
						x * data->mms, y * data->mms) == -1)
					return (print_error("MLX error", EXIT_FAILURE));
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

static int	display_images(t_data *data)
{
	t_player	*p;
	int			height;

	p = &data->player;
	height = data->mms / 4;
	fill_background(data);
	if (mlx_image_to_window(data->mlx, data->background, 0, 0))
		return (print_error("MLX error", EXIT_FAILURE));
	if (mlx_image_to_window(data->mlx, data->world, 0, 0))
		return (print_error("MLX error", EXIT_FAILURE));
	if (mlx_image_to_window(data->mlx, data->grid, 0, 0))
		return (print_error("MLX error", EXIT_FAILURE));
	fill_square(p->image, data->mms / 4, data->mms / 4, COP);
	if (mlx_image_to_window(data->mlx, p->image, \
		p->x * data->mms - data->mms / 8, \
		p->y * data->mms - data->mms / 8) == -1)
		return (print_error("MLX error", EXIT_FAILURE));
	if (display_minimap(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	graphics(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data->mlx)
		return (print_error("No MLX", EXIT_FAILURE));
	if (create_images(data))
		return (EXIT_FAILURE);
	print_integer_map(data);
	mlx_loop_hook(data->mlx, &exit_hook, data);
	mlx_loop_hook(data->mlx, &gameloop, data);
	if (display_images(data))
		return (EXIT_FAILURE);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
