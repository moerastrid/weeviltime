/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 14:43:10 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/27 17:19:24 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max.y)
	{
		//printf("%s\n", data->map_array[i]);
		i++;
	}
}
