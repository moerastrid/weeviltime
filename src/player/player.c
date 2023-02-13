/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 15:50:18 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 14:59:10 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	get_player_spawn(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("Test\n");
	printf("Map size: %i\n", data->map_size);
	printf("Test\n");
	// data->distance_to_wall = 0.5;
	printf("Map size: %d\n", data->map_size);
	while (i < data->map_size)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			printf("Test: %d\n", j);
			if (data->map_array[i][j] == 'N')
			{
				printf("Test\n");
				while (data->map_array[i][j] != '1')
				{
					i--;
					data->distance_to_wall += 1;
				}
				printf("Test\n");
				data->player.direction = data->map_array[i][j];
				return (EXIT_SUCCESS);
			}
			j++;
		}
		i++;
	}
	printf("Test\n");
	return (EXIT_FAILURE);
}


	// else if (data->map_array[i][j] == 'E')
			// {
			// 	while (data->map_array[i][j] != '1')
			// 	{
			// 		j++;
			// 		data->distance_to_wall += 1;
			// 	}
			// 	data->player.direction = data->map_array[i][j];
			// 	break ;
			// }
			// else if (data->map_array[i][j] == 'S')
			// {
			// 	while (data->map_array[i][j] != '1')
			// 	{
			// 		i++;
			// 		data->distance_to_wall += 1;
			// 	}
			// 	data->player.direction = data->map_array[i][j];
			// 	break ;
			// }
			// else if (data->map_array[i][j] == 'W')
			// {
			// 	while (data->map_array[i][j] != '1')
			// 	{
			// 		j--;
			// 		data->distance_to_wall += 1;
			// 	}
			// 	data->player.direction = data->map_array[i][j];
			// 	break ;
			// }

			
// int	init_player_data(t_data *data)
// {
// 	int		**arr;
// 	int		left_x;
// 	int		right_x;
// 	int		y;
// 	bool	done;

// 	if (get_player_spawn(data) != EXIT_SUCCESS)
// 		return (EXIT_FAILURE);
// 	// y = data->player.direction;
// 	// left_x = data->player.x;
// 	// right_x = data->player.x;
// 	// done = false;
// 	// while (done == false)
// 	// {
// 	// 	done = true;
// 	// 	if (data->map_array[y][left_x - 1] == '1')
// 	// 		save(data->map_array[y][left_x - 1]);
// 	// 	else
// 	// 	{
// 	// 		left_x--;
// 	// 		if (data->map_array[y - 1][left_x] == '1')
// 	// 			save(data->map_array[y - 1][left_x]);
// 	// 	}
// 	// }
// 	return (EXIT_SUCCESS);
// }
