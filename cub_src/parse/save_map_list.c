/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 17:46:24 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 18:47:58 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static void	save_max(t_data *data, char *line)
{
	int	length;

	length = ft_strlen(line);
	if (data->max.x < length)
		data->max.x = length;
	data->max.y++;
}

static void	skip_new_lines(t_par *par, char **line)
{
	while (*line != NULL && *line[0] == '\n')
	{
		free(*line);
		*line = get_next_line(par->fd_cub);
	}
}

int	save_map_list(t_data *data, t_par *par, char **line)
{
	char	*temp;

	temp = *line;
	skip_new_lines(par, &temp);
	while (temp != NULL)
	{
		if (temp[0] == '\n')
			break ;
		if (ft_strlen(temp) > 0 && temp[ft_strlen(temp) - 1] == '\n')
			temp[ft_strlen(temp) - 1] = '\0';
		ft_lstadd_back(&par->map_lines, ft_lstnew(temp));
		save_max(data, temp);
		free(temp);
		temp = get_next_line(par->fd_cub);
	}
	//skip_new_lines(par, line);
	if (data->max.y < 1 || temp != NULL)
	{
		if (temp != NULL)
			free(temp);
		return (print_error("Wrong map format"));
	}
	return (EXIT_SUCCESS);
}
