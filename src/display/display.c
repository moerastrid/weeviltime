/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:02 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/08 20:20:48 by astrid        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

bool	display(t_data *data)
{
	if (!background(data))
		return (false);
	if (!build(data))
		return (false);
	if (!grid(data))
		return (false);
	return (true);
}
