/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:22:19 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 11:24:47 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	print_error(char *s)
{
	printf("%s\n", s);
	return (EXIT_FAILURE);
}

int	check_map_tabs(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_size)
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

int	check_all(t_data *data, int i, int j)
{
	if (i == 0 || i == (data->map_size - 1))
		return (print_error("First or last line"));
	if (j == 0 || data->map_array[i][j + 1] == '\n')
		return (print_error("left or right edge"));
	if (i != 0 && (ft_strlen(data->map_array[i - 1]) < 2
			|| (size_t)j > ft_strlen(data->map_array[i - 1]) - 2))
		return (print_error("Above line too short"));
	if (i != data->map_size - 1 && (ft_strlen(data->map_array[i + 1]) < 2
			|| (size_t)j > ft_strlen(data->map_array[i + 1]) - 2))
		return (print_error("Below line too short"));
	if (data->map_array[i - 1][j] == ' '
		|| data->map_array[i + 1][j] == ' '
		|| data->map_array[i][j - 1] == ' '
		|| data->map_array[i][j + 1] == ' ')
		return (print_error("Bordering character"));
	return (EXIT_SUCCESS);
}

int	check_map_spaces(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_size)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == '0')
			{
				if (check_all(data, i, j) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
