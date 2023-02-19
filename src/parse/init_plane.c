/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_plane.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 14:15:30 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/16 21:38:21 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

// int n naar een enum veranderen
static bool	check_and_set_plane(char *line, int n, t_plane *plane, t_par *pars)
{
	char	**temp_arr;

	if (pars->color_check[n] != true)
	{
		pars->color_check[n] = true;
		temp_arr = ft_single_split(&line[2], ',');
		plane->color = make_color(ft_atoi(temp_arr[0]),
				ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
		free(temp_arr);
		return (true);
	}
	return (false);
}

// lengte van temp array checken voor beiden (bij strncmp)
bool	init_plane(t_data *data, char *line, t_par *pars)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		return (check_and_set_plane(line, C, &data->ceiling, pars));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (check_and_set_plane(line, F, &data->floor, pars));
	return (false);
}
