/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 14:39:38 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/14 00:50:50 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

		//save_map(map_fd, temp_, data, s);
		//convert_map(data);
		//print_map(data);		// Kan je aan en uit zetten
		//check_map_tabs(data);
		//check_map_spaces(data);

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

//int	save_map(int map, t_data *data, char *line)
//{
//	char	*temp_line;

//	temp_line = line;
//	while (temp_line != NULL)
//	{
//		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
//		{
//			ft_lstclear(&data->map_lines, &free);
//			free(temp_line);
//			return (EXIT_FAILURE);
//		}
//		temp_line = get_next_line(map);
//		if (data->map.x < (int)ft_strlen(temp_line))
//			data->map.x = ft_strlen(temp_line);
//		data->map.y++;
//	}
//	if (data->map.y < 1)
//		return (EXIT_FAILURE);
//	return (EXIT_SUCCESS);
//}

//void	free_map_array(char **map_array)
//{
//	int	y;

//	if (map_array == NULL)
//		return ;
//	y = 0;
//	while (map_array[y] != NULL)
//	{
//		free(map_array[y]);
//		y++;
//	}
//	free(map_array);
//}

//int	convert_map(t_data *data)
//{
//	int		rows;
//	int		y;
//	char	**map_array;
//	t_list	*map_lines;

//	map_lines = data->map_lines;
//	rows = ft_lstsize(map_lines);
//	map_array = malloc(((size_t)rows + 1) * sizeof(char *));
//	if (map_array == NULL)
//		return (EXIT_FAILURE);
//	y = 0;
//	while (y < rows)
//	{
//		map_array[y] = strdup(map_lines->content);
//		if (map_array[y] == NULL)
//		{
//			free_map_array(map_array);
//			return (EXIT_FAILURE);
//		}
//		map_lines = map_lines->next;
//		y++;
//	}
//	map_array[y] = NULL;
//	data->map_array = map_array;
//	return (EXIT_SUCCESS);
//}



