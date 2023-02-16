/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_plane.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 14:15:30 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/16 15:54:46 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"


// bool	init_plane(t_data *data, char *line)
// {
// 	char	**temp_arr;

// 	if (ft_strncmp(line, "C ", 2) == 0)		// lengte van temp array checken voor beiden
// 	{
// 		if (data->color_check[C] != true)
// 		{
// 			data->color_check[C] = true;
// 			temp_arr = ft_split(&line[2], ',');
// 			data->ceiling.color = make_color(ft_atoi(temp_arr[0]),
// 					ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
// 			free_array(temp_arr);
// 			return (true);
// 		}
// 		return (false);
// 	}
// 	else if (ft_strncmp(line, "F ", 2) == 0)
// 	{
// 		if (data->color_check[F] != true)
// 		{
// 			data->color_check[F] = true;
// 			temp_arr = ft_split(&line[2], ',');
// 			data->floor.color = make_color(ft_atoi(temp_arr[0]),
// 					ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
// 			free_array(temp_arr);
// 			return (true);
// 		}
// 		return (false);
// 	}
// 	else
// 		return (false);
// 	return (true);
// }

static bool	check_and_set_plane(t_data *data, char *line, int n, t_plane *plane)	// int n naar een enum veranderen
{
	char	**temp_arr;

	if (data->color_check[n] != true)
	{
		data->color_check[n] = true;
		temp_arr = ft_split(&line[2], ',');
		plane->color = make_color(ft_atoi(temp_arr[0]),
				ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
		free_array(temp_arr);
		return (true);
	}
	return (false);
}

bool	init_plane(t_data *data, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)		// lengte van temp array checken voor beiden
		return (check_and_set_plane(data, line, C, &data->ceiling));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (check_and_set_plane(data, line, F, &data->floor));
	return (false);
}
