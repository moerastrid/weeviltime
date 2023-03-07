/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 13:52:34 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/07 12:01:56 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

int	get_mapdata(t_data *data, t_par *par, char *line)
{
	if (get_map(data, par, line))
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
				return (EXIT_FAILURE);
			}
		}
		else
			return (get_mapdata(data, par, line));
		free(line);
		line = get_next_line(par->fd_cub);
	}
	return (EXIT_FAILURE);
}
