/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compatibalize_map.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 14:08:51 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/27 17:40:03 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	print_integer_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->map_y * data->map_x))
	{
		if ((i % data->map_x) == 0)
			printf("\n");
		printf("%d", data->final_map[i]);
		i++;
	}
	printf("\n");
}

int	compatibalize_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->final_map = malloc(data->map_x * data->map_y * sizeof(int));
	while (data->map_array[i] != NULL)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == ' ' || data->map_array[i][j] == 'N'
				|| data->map_array[i][j] == 'S' || data->map_array[i][j] == 'E'
				|| data->map_array[i][j] == 'W')
				data->final_map[j + (data->map_x * i)] = 0;
			else
				data->final_map[j + (data->map_x * i)]
					= data->map_array[i][j] - '0';
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
