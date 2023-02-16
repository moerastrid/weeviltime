/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 13:53:23 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/16 21:41:21 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

// moet dit reworken om de juiste error te geven
static bool	set_wall(t_data *data, char *line, int n, mlx_image_t *wall, t_par *pars)
{
	mlx_texture_t	*texture;

	if (pars->wall_check[n] != true)
	{
		//pars->wall_check[n] = true;
		//if (line[ft_strlen(line) - 1] == '\n')
		//	line[ft_strlen(line) - 1] = '\0';
		texture = mlx_load_png(&line[3]);
		if (texture == NULL)
			return (false);
		wall = mlx_texture_to_image(data->mlx, texture);
		//if (wall == NULL)
		//	return (false);
		//mlx_delete_texture(texture);
		return (true);
	}
	return (false);
}

bool	init_walls(t_data *data, char *line, t_par *pars)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_wall(data, line, EA, data->walls.wall_east, pars));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_wall(data, line, NO, data->walls.wall_north, pars));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_wall(data, line, WE, data->walls.wall_west, pars));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_wall(data, line, SO, data->walls.wall_south, pars));
	return (false);
}
