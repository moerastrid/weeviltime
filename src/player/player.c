/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 15:50:18 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/20 14:37:25 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

	// data->distance_to_wall = 0.5;
int	get_player_spawn(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_y)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == 'N' || data->map_array[i][j] == 'S'
				|| data->map_array[i][j] == 'E' || data->map_array[i][j] == 'W')
			{
				data->player.x = j;
				data->player.y = i;
				data->player.direction = data->map_array[i][j];
				return (EXIT_SUCCESS);
			}
			j++;
		}
		i++;
	}
	return (EXIT_FAILURE);
}
