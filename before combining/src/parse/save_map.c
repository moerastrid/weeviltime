/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 14:16:34 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/27 17:38:06 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"
static void	save_line_length(t_data *data, char *temp_line)
{
	int	length;

	length = ft_strlen(temp_line);
	if (data->map_x < length)
		data->map_x = length;
}

int	save_map(int map, t_data *data, char *line)
{
	char	*temp_line;

	data->map_y = 0;
	data->map_x = 0;
	if (map < 0)
		return (EXIT_FAILURE);
	data->map_lines = NULL;
	temp_line = line;
	while (temp_line[0] == '\n')
	{
		free(temp_line);
		temp_line = get_next_line(map);
	}
	while (temp_line != NULL)
	{
		if (temp_line[0] == '\n')
			break ;
		if (temp_line[ft_strlen(temp_line) - 1] == '\n')
			temp_line[ft_strlen(temp_line) - 1] = '\0';
		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
		{
			ft_lstclear(&data->map_lines, &free);
			free(temp_line);
			return (EXIT_FAILURE);
		}
		save_line_length(data, temp_line);
		temp_line = get_next_line(map);
		data->map_y++;
	}
	while (temp_line != NULL)
	{
		if (temp_line[0] != '\n')
		{
			free(temp_line);
			return (EXIT_FAILURE);
		}
		free(temp_line);
		temp_line = get_next_line(map);
	}
	if (data->map_y < 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}