/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 17:03:25 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:52:28 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Writes maximum n zero's to string s

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
