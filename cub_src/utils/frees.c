/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frees.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 15:23:16 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 18:12:34 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_par(t_par *par)
{
	if (par->wall_check)
		free(par->wall_check);
	if (par->color_check)
		free(par->color_check);
	if (par->maplst)
		ft_lstclear(&par->maplst, &free);
	if (par->maparray)
		free_array(par->maparray);
}

void	free_data(t_data	*data)
{
	if (!data)
		return ;
	if (data->walls)
	{
		if (data->walls[NO].path)
			free(data->walls[NO].path);
		if (data->walls[SO].path)
			free(data->walls[SO].path);
		if (data->walls[WE].path)
			free(data->walls[WE].path);
		if (data->walls[EA].path)
			free(data->walls[EA].path);
		free(data->walls);
	}
	if (data->planes)
		free(data->planes);
	if (data->final_map)
		free(data->final_map);
}
