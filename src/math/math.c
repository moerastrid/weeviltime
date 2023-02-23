/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:09 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/23 14:00:24 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"



static float	calculate_distance(t_data *data, float angle)
{
	float	distance;
	float	temp;
	t_co	pos;
	t_co	result;
	int		i;
	int		b;
	int		j;

	i = 0;
	j = 0;
	distance = INT_MAX;
	temp = INT_MAX;
	result.y = 0;
	result.x = 0;
	pos.x = data->player.x + 0.5;
	pos.y = data->player.y + 0.5;
	angle += data->player.direction;

	//line formula:
	b = (pos.y - atan(angle) * pos.x);
	while (data->map_array[j])
	{
		while (data->map_array[j][i])
		{
			if (data->map_array[j][i] == '1')
			{
				temp = ((pos.y - j) * (pos.y - j) + (pos.x - i) * (pos.x - i));
				if (temp < distance)
					distance = temp;
			}
			i++;
		}
		j++;
	}
	// printf("data player\tx: %f\ty: %f\tangle: %f\ndistance: %f\n\n", pos.x, pos.y, angle, distance);
	return (sqrt(distance));
}

float	calculate_height(t_data *data, int x)
{
	float	height;
	float	distance;
	float	angle;

	(void)data;
	angle = -0.2 * M_PI + ((x * 0.4 * M_PI) / WIDTH);
	if (angle >= M_PI * 2)
		angle = angle - M_PI * 2;
	if (angle < 0)
		angle = angle + 2 * M_PI;
	distance = calculate_distance(data,angle );
	height = cos(angle) * ((HEIGHT / 2) / distance);
	height = ((HEIGHT / 2) / distance);
	return (height);
}
