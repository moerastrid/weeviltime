/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 14:08:51 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/03 19:40:55 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	set_tile(t_data *data, t_par *par, int i, int *j)
{
	char	c;

	c = par->maparray[i][*j];
	if (c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		data->map[*j + (data->max.x * i)] = 0;
	else
		data->map[*j + (data->max.x * i)] = par->maparray[i][*j] - '0';
	if (par->maparray[i][*j + 1] == '\0')
	{
		(*j)++;
		while (*j < data->max.x)
		{
			data->map[(*j + (data->max.x * i))] = 0;
			(*j)++;
		}
	}
}

int	set_map(t_data *data, t_par *par)
{
	int	i;
	int	j;

	i = 0;
	data->map = malloc(data->max.x * data->max.y * sizeof(int));
	if (!data->map)
		return (print_error("malloc error"));
	while (par->maparray[i] != NULL)
	{
		j = 0;
		while (par->maparray[i][j] != '\0')
		{
			set_tile(data, par, i, &j);
			j++;
		}
		i++;
	}
	if (((0.25 * WIDTH) / data->max.x) > ((0.25 * HEIGHT) / data->max.y))
		data->mms = 2 + (0.25 * HEIGHT) / data->max.y;
	else
		data->mms = 2 + ((0.25 * WIDTH) / data->max.x);
	return (EXIT_SUCCESS);
}
