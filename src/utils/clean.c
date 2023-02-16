/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 20:50:09 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/16 21:16:46 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	free_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	clean_everything(t_data *data)
{
	mlx_delete_image(data->mlx, data->walls.wall_north);
	mlx_delete_image(data->mlx, data->walls.wall_south);
	mlx_delete_image(data->mlx, data->walls.wall_west);
	mlx_delete_image(data->mlx, data->walls.wall_east);
	mlx_terminate(data->mlx);
	free_array(data->map_array);
}
