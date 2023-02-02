/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/02 16:21:06 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#define WIDTH 512
#define HEIGHT 512

// int32_t	main(void)
// {
// 	t_data	data;

// 	data.mlx = mlx_init(800, 800, "MLX42", false);
// 	return (EXIT_SUCCESS);
// }

static mlx_image_t* img;

void hook(void* param)
{
	const mlx_t* mlx = param;

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
	mlx_t			*mlx;
	mlx_texture_t	*texture;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return(EXIT_FAILURE);

	texture = mlx_load_png("src/dungeonTileset.png");
	img = mlx_texture_area_to_image(mlx, texture, (uint32_t[2]){0, 80}, (uint32_t[2]){80, 80});
	mlx_delete_texture(texture);
	// img = mlx_new_image(mlx, 128, 128);
	// memset(img->pixels, 255, img->width * img->height * sizeof(int));
	mlx_image_to_window(mlx, img, 0, 0);

	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
