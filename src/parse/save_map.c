/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 14:16:34 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/23 16:49:50 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	save_map(int map, t_data *data, char *line)
{
	int		map_y;
	char	*temp_line;

	map_y = 0;
	if (map < 0)
		return (EXIT_FAILURE);
	data->map_lines = NULL;
	temp_line = line;
	while (temp_line != NULL)
	{
		// printf("%s\n", temp_line);
		// if (temp_line[0] == '\n')
		// 	break ;
		if (temp_line[ft_strlen(temp_line) - 1] == '\n')
			temp_line[ft_strlen(temp_line) - 1] = '\0';
		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
		{
			ft_lstclear(&data->map_lines, &free);
			free(temp_line);
			return (EXIT_FAILURE);
		}
		temp_line = get_next_line(map);
		map_y++;
	}
	if (map_y < 1)
		return (EXIT_FAILURE);
	data->map_y = map_y;
	return (EXIT_SUCCESS);
}
