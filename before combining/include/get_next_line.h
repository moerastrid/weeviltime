/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/08 13:55:40 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:49:47 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h> // OPEN_MAX
# include <sys/select.h> // FD_SETSIZE
# include <stddef.h> // size_t

# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX FD_SETSIZE
# endif

char	*get_next_line(int fd);

#endif
