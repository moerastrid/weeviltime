/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 14:15:51 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:53:23 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Writes a string

#include "libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (-1);
	len = ft_strlen(s);
	return (write(fd, s, len));
}
