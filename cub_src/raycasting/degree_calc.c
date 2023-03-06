/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   degree_calc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 20:53:40 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/06 21:21:04 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

//	utils

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

float	fix_ang(float a)
{
	if (a > 359.0)
		a -= 360.0;
	if (a < 0)
		a += 360.0;
	return (a);
}
