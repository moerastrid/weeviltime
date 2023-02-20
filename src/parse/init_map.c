/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 13:52:34 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/20 14:02:13 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	init_map(int map, t_data *data)		//initialiseert de ceiling en floor kleuren + koppelt png bestanden aan de individuele muur-kanten
{
	char	*temp_line;
	int		element_count;

	temp_line = get_next_line(map);
	element_count = 0;
	data->wall_check = malloc(4 * sizeof(bool));	//protecten
	if (data->wall_check == NULL)
		return (EXIT_FAILURE);
	ft_bzero(data->wall_check, 4 * sizeof(bool));
	data->color_check = malloc(2 * sizeof(bool));
	if (data->color_check == NULL)
		return (EXIT_FAILURE);
	ft_bzero(data->color_check, 2 * sizeof(bool));
	while (temp_line != NULL)
	{
		if (element_count < 6)
		{
			if (init_wall(data, temp_line) || init_plane(data, temp_line))
				element_count++;
			free(temp_line);
		}
		else
		{
			free(data->wall_check);
			free(data->color_check);
			save_map(map, data, temp_line);
			convert_map(data);
			ft_lstclear(&data->map_lines, &free);
			if (check_map(data) == EXIT_FAILURE
				|| check_player_spawn(data) == EXIT_FAILURE)
			{
				free_array(data->map_array);
				return (EXIT_FAILURE);
			}
			print_map(data);		// Kan je aan en uit zetten
		}
		temp_line = get_next_line(map);
	}
	if (element_count != 6)
	{
		free(data->wall_check);
		free(data->color_check);
		printf("Missing color/texture arguments\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// //initialiseert de ceiling en floor kleuren 
// //+ koppelt png bestanden aan de individuele muur-kanten
// int	init_map(t_data *data, t_par *pars)
// {
// 	char	*temp_line;
// 	int		elem_count;

// 	(void)data;
// 	elem_count = 0;
// 	//pars->wall_check = ft_calloc(4, sizeof(bool));
// 	//if (pars->wall_check == NULL)
// 	//	return (EXIT_FAILURE);
// 	//pars->color_check = ft_calloc(2, sizeof(bool));
// 	//if (pars->color_check == NULL)
// 	//	return (EXIT_FAILURE);
// 	temp_line = get_next_line(pars->fd);
// 	while (temp_line != NULL)
// 	{
// 		if (elem_count < 6)
// 		{
// 			//if (init_walls(data, pars, temp_line) || init_plane(data, temp_line))
// 				elem_count++;
// 			free(temp_line);
// 		}
// 		//else
// 		//{
// 		//	free(pars->wall_check);
// 		//	free(pars->color_check);
// 		//	save_map(map, data, temp_line);
// 		//	convert_map(data, pars);
// 		//	if (check_map(data) == EXIT_FAILURE
// 		//		|| check_player_spawn(data) == EXIT_FAILURE)
// 		//	{
// 		//		//free_array(data->map_array);
// 		//		return (EXIT_FAILURE);
// 		//	}
// 		//	print_map(data);
// 		//}
// 		temp_line = get_next_line(pars->fd);
// 	}
// 	if (elem_count != 6)
// 	{
// 		free(pars->wall_check);
// 		free(pars->color_check);
// 		printf("Missing color/texture arguments\n");
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }
