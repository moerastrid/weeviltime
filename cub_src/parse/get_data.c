/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 13:52:34 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/22 20:19:26 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

int	get_data(t_data *data, t_par *par)
{
	char	*temp_line;
	int		elem_count;

	temp_line = get_next_line(par->fd_cub);
	elem_count = 0;
	while (temp_line != NULL)
	{
		if (elem_count < 6)
		{
			if (get_elem(data, par, temp_line) == true)
				elem_count++;
		}
		free(temp_line);
		temp_line = get_next_line(par->fd_cub);
	}
	return (EXIT_FAILURE);
}
