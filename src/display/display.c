/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:02 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 16:07:21 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

bool	display(t_data *data)
{
	if (!background(data))
		return (false);
	if (!build(data))
		return (false);
	grid(data);
	return (true);
}