/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/02 15:39:01 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static mlx_image_t* img;

void	hook(void* param)
{
	const mlx_t	*mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t*	mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "Weevil Time!", true);
	if (!mlx)
		return (EXIT_FAILURE);
	img = mlx_new_image(mlx, 128, 128);
	memset(img->pixels, 255, img->width * img->height * sizeof(int));
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}