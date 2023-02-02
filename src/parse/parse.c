/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/02 22:02:18 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	parse(int argc, char **argv, t_data *data)
{
	data->mlx = NULL;
	data->wall = NULL;
	data->sky.color = SKYCOLOR;
	data->floor.color = FLOORCOLOR;
	(void)argc;
	(void)argv;
	return (0);
}
