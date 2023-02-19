/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:22:19 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/16 20:32:02 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	check_every_zero(t_data *data, int i, int j)
{
	if (i == 0 || i == (data->map_y - 1))
		return (print_error("First or last line"));
	if (j == 0 || data->map_array[i][j + 1] == '\0')
		return (print_error("left or right edge"));
	if (i != 0 && (ft_strlen(data->map_array[i - 1]) < 1
			|| (size_t)j > ft_strlen(data->map_array[i - 1]) - 1))
		return (print_error("Above line too short"));
	if (i != data->map_y - 1 && (ft_strlen(data->map_array[i + 1]) < 1
			|| (size_t)j > ft_strlen(data->map_array[i + 1]) - 1))
		return (print_error("Below line too short"));
	if (data->map_array[i - 1][j] == ' '
		|| data->map_array[i + 1][j] == ' '
		|| data->map_array[i][j - 1] == ' '
		|| data->map_array[i][j + 1] == ' ')
		return (print_error("Bordering character"));
	return (EXIT_SUCCESS);
}

static int	check_map_spaces(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_y)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == '0')
			{
				if (check_every_zero(data, i, j) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	check_map_tabs(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_y)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == '\t')
				return (print_error("NO TABS!!!"));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_map(t_data *data)
{
	if (check_map_tabs(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map_spaces(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
