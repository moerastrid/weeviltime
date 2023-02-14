/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_and_convert_map.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 14:39:38 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/14 15:42:13 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	save_map(int map, t_data *data, char *line)
{
	int		map_size;
	char	*temp_line;

	map_size = 0;
	if (map < 0)
		return (EXIT_FAILURE);
	data->map_lines = NULL;
	temp_line = line;
	while (temp_line != NULL)
	{
		if (temp_line[ft_strlen(temp_line) - 1] == '\n')
			temp_line[ft_strlen(temp_line) - 1] = '\0';
		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
		{
			ft_lstclear(&data->map_lines, &free);
			free(temp_line);
			return (EXIT_FAILURE);
		}
		temp_line = get_next_line(map);
		map_size++;
	}
	if (map_size < 1)
		return (EXIT_FAILURE);
	data->map_size = map_size;
	return (EXIT_SUCCESS);
}

void	free_map_array(char **map_array)
{
	int	y;

	if (map_array == NULL)
		return ;
	y = 0;
	while (map_array[y] != NULL)
	{
		free(map_array[y]);
		y++;
	}
	free(map_array);
}

int	convert_map(t_data *data)
{
	int		rows;
	int		y;
	char	**map_array;
	t_list	*map_lines;

	map_lines = data->map_lines;
	rows = ft_lstsize(map_lines);
	map_array = malloc(((size_t)rows + 1) * sizeof(char *));
	if (map_array == NULL)
		return (EXIT_FAILURE);
	y = 0;
	while (y < rows)
	{
		map_array[y] = strdup(map_lines->content);
		if (map_array[y] == NULL)
		{
			free_map_array(map_array);
			return (EXIT_FAILURE);
		}
		map_lines = map_lines->next;
		y++;
	}
	map_array[y] = NULL;
	data->map_array = map_array;
	return (EXIT_SUCCESS);
}
