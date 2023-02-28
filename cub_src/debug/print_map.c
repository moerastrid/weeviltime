/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 14:43:10 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/28 19:56:35 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	print_par_map(t_par *par)
{
	int	i;

	i = 0;
	while (par->maparray[i])
	{
		printf("%s\n", par->maparray[i]);
		i++;
	}
}

void	print_integer_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->max.y * data->max.x))
	{
		if ((i % data->max.x) == 0)
			printf("\n");
		printf("%d", data->map[i]);
		i++;
	}
	printf("\n");
}
