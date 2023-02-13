/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:23:34 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:52:24 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Allocates enough space for count objects that are size bytes
// The allocated memory is filled with zero's

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;

	s = malloc(count * size);
	if (s)
		ft_bzero(s, count * size);
	return (s);
}
