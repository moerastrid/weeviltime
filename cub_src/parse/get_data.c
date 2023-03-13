/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 13:52:34 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/13 17:19:15 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static char	*check_invalid_line(t_par *par, char *line)
{
	char	*temp_line;
	int		i;

	temp_line = ft_strdup(line);
	free(line);
	i = 0;
	while (temp_line != NULL && temp_line[0] == '\n')
	{
		free(temp_line);
		temp_line = get_next_line(par->fd_cub);
	}
	while (temp_line[i] == ' ')
		i++;
	if (temp_line[i] != '1')
	{
		free(temp_line);
		return (NULL);
	}
	return (temp_line);
}

int	get_mapdata(t_data *data, t_par *par, char *line)
{
	char	*temp;

	temp = check_invalid_line(par, line);
	if (temp == NULL)
		return (print_error("invalid line in map", EXIT_FAILURE));
	if (get_map(data, par, temp))
		return (EXIT_FAILURE);
	if (set_map(data, par) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_data(t_data *data, t_par *par)
{
	char	*line;
	int		elem_count;
	int		check_elem;

	line = get_next_line(par->fd_cub);
	elem_count = 0;
	while (line != NULL)
	{
		if (elem_count < 6)
		{
			check_elem = get_elem(data, par, line);
			if (check_elem == 1)
				elem_count++;
			else if (check_elem == -1)
			{
				free(line);
				return (print_error("invalid setup args", EXIT_FAILURE));
			}
		}
		else
			return (get_mapdata(data, par, line));
		free(line);
		line = get_next_line(par->fd_cub);
	}
	return (EXIT_FAILURE);
}
