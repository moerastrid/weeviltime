/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/09 15:50:18 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/16 20:39:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/cub.h"

//	// data->distance_to_wall = 0.5;
//int	get_player_spawn(t_data *data)
//{
//	int	i;
//	int	j;

//	i = 0;
//	j = 0;
//	while (i < data->map_y)
//	{
//		j = 0;
//		while (data->map_array[i][j] != '\0')
//		{
//			if (data->map_array[i][j] == 'N')
//			{
//				while (data->map_array[i][j] != '1')
//					i--;
//				data->player.direction = data->map_array[i][j];
//				return (EXIT_SUCCESS);
//			}
//			j++;
//		}
//		i++;
//	}
//	return (EXIT_FAILURE);
//}
