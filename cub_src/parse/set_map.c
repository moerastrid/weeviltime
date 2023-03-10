/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 14:08:51 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/13 20:25:18 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	set_tile(t_data *data, t_par *par, int i, int j)
{
	char	c;

	c = par->maparray[i][j];
	if (c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		data->map[i][j] = 0;
	else
	{
		data->map[i][j] = par->maparray[i][j] - '0';
	}
	if (par->maparray[i][j + 1] == '\0')
	{
		(j)++;
		while (j < data->max.x)
		{
			data->map[i][j] = 0;
			(j)++;
		}
	}
}

int	allocate_int_map(t_data *data)
{
	int	i;

	i = 0;
	data->map = malloc(data->max.y * sizeof(int *));
	if (!data->map)
		return (print_error("malloc error", EXIT_FAILURE));
	while (i < data->max.y)
	{
		data->map[i] = malloc(sizeof(int) * data->max.x);
		if (!data->map[i])
		{
			while (i >= 0)
			{
				free(data->map[i]);
				i--;
			}
			free(data->map);
			return (print_error("malloc error", EXIT_FAILURE));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	fill_map(t_data *data, t_par *par, int i, int *j)
{
	char	c;

	c = par->maparray[i][*j];
	if (c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		data->map[i][*j] = 0;
	else
		data->map[i][*j] = par->maparray[i][*j] - '0';
	if (par->maparray[i][*j + 1] == '\0')
	{
		(*j)++;
		while (*j < data->max.x)
		{
			data->map[i][*j] = 0;
			(*j)++;
		}
	}
}

int	set_map(t_data *data, t_par *par)
{
	int		i;
	int		j;

	allocate_int_map(data);
	i = 0;
	while (i < data->max.y)
	{
		j = 0;
		while (j < data->max.x)
		{
			fill_map(data, par, i, &j);
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
