/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 17:02:22 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 18:20:57 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

int	get_map(t_data *data, t_par *par, char **line)
{
	save_map_list(data, par, line);
	//convert_map(data);
	//if (check_map(data) == EXIT_FAILURE)
	//{
	//	free_array(data->map_array);
	//	return (EXIT_FAILURE);
	//}
	//print_map(data);		// Kan je aan en uit zetten
	return (EXIT_SUCCESS);
}
