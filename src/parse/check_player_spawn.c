/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_player_spawn.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 13:54:28 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/20 14:44:29 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	check_player_spawn(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (data->map_array[i] != NULL)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == 'N'
				|| data->map_array[i][j] == 'S'
				|| data->map_array[i][j] == 'W'
				|| data->map_array[i][j] == 'E')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
