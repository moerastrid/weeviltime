/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 13:42:38 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	set_default_values(t_data *data)
{
	data->mlx = NULL;
	data->wall = NULL;
	data->sky.color = SKYCOLOR;
	data->floor.color = FLOORCOLOR;
	data->camx = WIDTH / 2;
	data->camy = HEIGHT / 2;
}

int	parse(int argc, char **argv, t_data *data)
{
	set_default_values(data);
	(void)argc;
	(void)argv;
	return (0);
}
