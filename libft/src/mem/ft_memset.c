/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:24:25 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:52:11 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Sets len amount of characters in s to c

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*g;

	g = (unsigned char *)s;
	while (len > 0)
	{
		len--;
		g[len] = (unsigned char)c;
	}
	return (s);
}
