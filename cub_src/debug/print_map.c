/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 14:43:10 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/28 15:43:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	print_map(t_par *par)
{
	int	i;

	i = 0;
	while (par->maparray[i])
	{
		printf("%s\n", par->maparray[i]);
		i++;
	}
}
