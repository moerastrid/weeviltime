/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:22:19 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/07 13:54:00 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static int	horizontal_edge(char *map_line, size_t line_length)
{
	size_t	i;

	i = 0;
	while (i != (line_length - 1))
	{
		if (map_line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_map_edge(t_data *data)
{
	size_t	line_length;
	char	*map_line;
	t_list	*map_lines;
	int		i;

	i = 0;
	map_lines = data->map_lines;
	line_length = ft_strlen(map_lines->content);
	map_line = map_lines->content;
	if (horizontal_edge(map_line, line_length) == 1)
		return (EXIT_FAILURE);
	while (map_lines->next != NULL)
	{
		map_line = map_lines->content;
		if (map_line[0] != '1' || map_line[line_length - 2] != '1')
			return (EXIT_FAILURE);
		map_lines = map_lines->next;
	}
	map_line = map_lines->content;
	if (horizontal_edge(map_line, line_length) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_map_spaces(t_data *data)		// main while loop aanpassen
{
	int	i;
	int	j;

	i = 0;
	while (i < 14)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == '0')
			{
				if (j == 0 || data->map_array[i][j + 1] == '\n')
					return (EXIT_FAILURE);
				if (ft_strlen(data->map_array[i - 1])
					< ft_strlen(data->map_array[i]))
					return (EXIT_FAILURE);
				if (ft_strlen(data->map_array[i + 1])
					< ft_strlen(data->map_array[i]))
					return (EXIT_FAILURE);
				if (data->map_array[i - 1][j] == ' ')
					return (EXIT_FAILURE);
				if (data->map_array[i + 1][j] == ' ')
					return (EXIT_FAILURE);
				if (data->map_array[i][j - 1] == ' ')
					return (EXIT_FAILURE);
				if (data->map_array[i][j + 1] == ' ')
					return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
