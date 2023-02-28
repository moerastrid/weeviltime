/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:24:01 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/22 20:37:14 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Checks if the given character is a digit
// Changed it to check for '-' '+' ' ' '\n' too.

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '-' || c == '+')
		return (1);
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}
