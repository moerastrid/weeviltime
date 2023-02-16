/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 14:11:59 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:53:04 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Writes a character

#include "libft.h"

ssize_t	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
