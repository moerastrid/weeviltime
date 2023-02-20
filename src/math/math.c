/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:09 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/20 14:19:35 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static float	calculate_distance(t_data *data)
{
	float	distance;
	t_co	myplace;

	distance = 4;
	myplace.x = data->player.x + 0.5;
	myplace.y = data->player.y + 0.5;
	printf("data player\tx: %d\ty: %d\n", data->player.x, data->player.y);
	return (distance);
}

float	calculate_height(t_data *data, int x)
{
	float	height;
	float	distance;
	float	angle;

	distance = calculate_distance(data);
	angle = -0.2 * 3.14 + ((x * 0.4 * 3.14) / WIDTH);
	height = cos(angle) * ((HEIGHT / 2) / distance);
	return (height);
}
