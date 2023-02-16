/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 13:51:23 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:52:37 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Adds the element new to the front of the list

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
