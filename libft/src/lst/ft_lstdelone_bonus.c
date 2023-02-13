/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 13:38:19 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/13 18:52:45 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Free's the memory of the given elements content using the function del

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del != NULL && lst != NULL)
		del(lst->content);
	free(lst);
}
