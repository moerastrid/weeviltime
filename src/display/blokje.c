/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   blokje.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 18:41:09 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/02 22:05:33 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

//void hook(void* param)
//{
//	const mlx_t* mlx = param;

//	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
//		mlx_close_window(mlx);
//	if (mlx_is_key_down(mlx, MLX_KEY_UP))
//		img->instances[0].y -= 5;
//	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
//		img->instances[0].y += 5;
//	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
//		img->instances[0].x -= 5;
//	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
//		img->instances[0].x += 5;
//}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->wall->instances[0].y -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->wall->instances[0].y += 5;
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		data->wall->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		data->wall->instances[0].x += 5;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

bool	build(t_data *data)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("include/textures/dungeonTexture.png");
	data->wall = mlx_texture_area_to_image(data->mlx, texture, (uint32_t[2]){0, 80}, (uint32_t[2]){80, 80});
	mlx_delete_texture(texture);
	mlx_image_to_window(data->mlx, data->wall, (data->mlx->width / 2) - 40, (data->mlx->height / 2) - 40);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	return (true);
}
