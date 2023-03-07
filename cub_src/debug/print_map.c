/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 14:43:10 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/07 11:50:33 by mforstho      ########   odam.nl         */
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
	int	j;

	i = 0;
	while (i < data->max.y)
	{
		j = 0;
		while (j < data->max.x)
		{
			printf("%d", data->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	// printf("\n");
}
