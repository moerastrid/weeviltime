/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:24:49 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:23:33 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Calculates the length of string c

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	if (!c)
		return (i);
	while (c[i] != '\0')
		i++;
	return (i);
}
