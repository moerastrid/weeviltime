/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compatibalize_map.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 14:08:51 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/28 18:02:07 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	print_integer_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->max.y * data->max.x))
	{
		if ((i % data->max.x) == 0)
			printf("\n");
		printf("%d", data->final_map[i]);
		i++;
	}
	printf("\n");
}

int	compatibalize_map(t_data *data, t_par *par)
{
	int	i;
	int	j;

	i = 0;
	data->final_map = malloc(data->max.x * data->max.y * sizeof(int));
	while (par->maparray[i] != NULL)
	{
		j = 0;
		while (par->maparray[i][j] != '\0')
		{
			if (par->maparray[i][j] == ' ' || par->maparray[i][j] == 'N'
				|| par->maparray[i][j] == 'S' || par->maparray[i][j] == 'E'
				|| par->maparray[i][j] == 'W')
				data->final_map[j + (data->max.x * i)] = 0;
			else
				data->final_map[j + (data->max.x * i)]
					= par->maparray[i][j] - '0';
			if (par->maparray[i][j + 1] == '\0')
			{
				j++;
				while (j < data->max.x)
				{
					data->final_map[(j + (data->max.x * i))] = 0;
					j++;
				}
				break ;
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
