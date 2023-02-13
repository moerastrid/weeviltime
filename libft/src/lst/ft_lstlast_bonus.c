/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 12:43:24 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:52:49 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Returns the last element of the list

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
