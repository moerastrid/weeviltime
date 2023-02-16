/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 12:09:19 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:53:00 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Iterates through the list to determine the size of the list

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
