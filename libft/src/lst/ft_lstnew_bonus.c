/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 18:08:24 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/27 20:15:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Returns a new element with the content data

#include "libft.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*lst;

	lst = ft_calloc(1, sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->content = data;
	lst->next = NULL;
	return (lst);
}
