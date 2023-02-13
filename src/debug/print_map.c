/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 14:43:10 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:38:36 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.y)
	{
		printf("%s", data->map_array[i]);
		i++;
	}
}
