/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 14:39:38 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/16 20:32:29 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static char	*check_lines(t_data *data, char *line, int map_fd, char *all_lines)
{
	while (line != NULL)
	{
		if (line[0] != '\n')
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(map_fd);
	}
	if (data->map.y == 0 || data->map.x == 0)
		return (NULL);
	return (all_lines);
}

static char	*get_lines(t_data *data, char *line, int map_fd)
{
	char	*temp;
	char	*all_lines;
	bool	empty_line;

	empty_line = false;
	all_lines = NULL;
	while (line != NULL && empty_line == false)
	{
		temp = all_lines;
		all_lines = ft_strjoin(all_lines, line);
		if (temp)
			free (temp);
		if (!all_lines)
			return (NULL);
		if (data->map.x < (int)ft_strlen(line))
			data->map.x = ft_strlen(line);
		free(line);
		line = get_next_line(map_fd);
		if (line[0] == '\n')
			empty_line = true;
		data->map.y++;
	}
	return (check_lines(data, line, map_fd, all_lines));
}

bool	set_map(t_data *data, char *line, int map_fd)
{
	char	*all_lines;

	all_lines = get_lines(data, line, map_fd);
	if (!all_lines)
		return (false);
	data->map_array = ft_split(all_lines, '\n');
	free(all_lines);
	return (true);
}
