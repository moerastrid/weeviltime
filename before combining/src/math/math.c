/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:09 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/22 15:38:11 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	find_direction(float angle, t_co	*direction)
{
	if (angle == 0 || angle == M_PI)
		direction->x = 0;
	else if (angle >= 0 && angle <= M_PI)
		direction->x = 1;
	else
		direction->x = -1;
	if (angle == M_PI_2 || angle == 3 * M_PI_2)
		direction->y = 0;
	else if (angle >= M_PI_2 && angle <= 3 * M_PI_2)
		direction->y = 1;
	else
		direction->y = -1;
}

static float	power_distance(t_co pos, t_co result)
{
	float a;
	float b;
	float c;

	a = (result.x - pos.x) * (result.x - pos.x);
	b = (result.y - pos.y) * (result.y - pos.y);
	c = a + b;
	return (c);
}

static float	calculate_distance(t_data *data, float angle)
{
	float	distance;
	float	temp;
	float	b;
	t_co	pos;
	t_co	result;
	t_co	direction;
	int		i;

	i = 0;
	distance = INT_MAX;
	temp = INT_MAX;
	result.y = 0;
	result.x = 0;
	find_direction(angle, &direction);
	pos.x = data->player.x + 0.5;
	pos.y = data->player.y + 0.5;
	
	//line formula: 
	b = (pos.y - atan(angle) * pos.x);
	if (direction.x < 0)
	{
		i = data->player.x;
		while (i > 0)
		{
			result.x = i;
			result.y = data->player.y + tan(angle) * result.x + b;
			if (data->map_array[(int)result.x][(int)result.y] == '1')
			{
				temp = power_distance(pos, result);
				if (temp < distance)
					distance = temp;
				printf("int x : %d\tint y : %d \n\n", (int)result.x, (int)result.y);
				break ;
			}
			i--;
		}
	}
	if (direction.x > 0)
	{
		i = data->player.x + 1;
		while (i < 6)
		{
			result.x = i;
			result.y = data->player.y + tan(angle) * result.x + b;
			//printf("hello?\n");
			if (data->map_array[(int)result.x][(int)result.y] == '1')
			{
				temp = power_distance(pos, result);
				if (temp < distance)
					distance = temp;
				printf("int x : %d\tint y : %d \n\n", (int)result.x, (int)result.y);
				break ;
			}
			i++;
		}
	}
	if (direction.x == 0)
		distance = (pos.y + b) * (pos.y + b);
	
	//i = 0;
	//if (direction.y > M_PI_2 && direction.y < M_PI_2 * 3)
	//{
	//	i = data->player.y;
	//	while (i > 0)
	//	{
	//		result.y = i;
	//		result.x = data->player.x + tan(angle) * i + b;
	//		temp = power_distance(pos, result);
	//		if (temp < distance)
	//		{
	//			distance = temp;
	//			printf("x : %d \ntemp1 : %f\n", i, temp);
	//		}
	//		i--;
	//	}
	//}
	//else
	//{
	//	i = data->player.y + 1;
	//	while (i < 10)
	//	{
	//		result.y = i;
	//		result.x = data->player.x + tan(angle) * i + b;
	//		temp = power_distance(pos, result);
	//		if (temp < distance)
	//		{
	//			distance = temp;
	//			printf("x : %d \ntemp2 : %f\n", i, temp);
	//		}
	//		i++;
	//	}
	//}
	//if (direction.y == 0)
	//	distance = (pos.x - (b / tan(angle))) * (pos.x - (b / tan(angle)));
	//printf("data player\tx: %f\ty: %f\tangle: %f\ndistance: %f\n\n", pos.x, pos.y, angle, distance);
	return (sqrt(distance));
}

float	calculate_height(t_data *data, int x)
{
	float	height;
	float	distance;
	float	angle;

	(void)data;
	angle = data->player.direction;
	angle += -0.2 * M_PI + ((x * 0.4 * M_PI) / WIDTH);
	if (angle >= M_PI * 2)
		angle = angle - M_PI * 2;
	if (angle < 0)
		angle = angle + 2 * M_PI; 
	distance = calculate_distance(data,angle);
	height = cos(angle) * ((HEIGHT / 2) / distance);
	//height = ((HEIGHT / 2) / distance);
	return (height);
}
