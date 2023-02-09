/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 15:50:18 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/09 16:38:41 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	get_player_spawn(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_size)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == 'N' || data->map_array[i][j] == 'E'
				|| data->map_array[i][j] == 'S' || data->map_array[i][j] == 'W')
			{
				data->player.x = j;
				data->player.y = i;
				data->player.direction = data->map_array[i][j];
				return (EXIT_SUCCESS);
			}
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	init_player_data(t_data *data)
{
	int		**arr;
	int		left_x;
	int		right_x;
	int		y;
	bool	done;

	if (get_player_spawn(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	// y = data->player.direction;
	// left_x = data->player.x;
	// right_x = data->player.x;
	// done = false;
	// while (done == false)
	// {
	// 	done = true;
	// 	if (data->map_array[y][left_x - 1] == '1')
	// 		save(data->map_array[y][left_x - 1]);
	// 	else
	// 	{
	// 		left_x--;
	// 		if (data->map_array[y - 1][left_x] == '1')
	// 			save(data->map_array[y - 1][left_x]);
	// 	}
	// }
	return (EXIT_SUCCESS);
}
