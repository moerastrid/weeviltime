/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:09 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/16 20:32:46 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

float	calculate_distance(void)
{
	return (4);
}

float	calculate_height(t_data *data, int x)
{
	float	height;
	float	distance;
	float	angle;

	(void)data;
	distance = calculate_distance();
	angle = -0.2 * 3.14 + ((x * 0.4 * 3.14) / WIDTH);
	height = cos(angle) * ((HEIGHT / 2) / distance);
	return (height);
}
