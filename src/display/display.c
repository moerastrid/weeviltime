/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:02 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/13 17:48:39 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

bool	display(t_data *data)
{
	if (!display_background(data))
		return (false);
	if (!display_blokje(data))
		return (false);
	if (!display_walls(data))
		return (false);
	return (true);
}
