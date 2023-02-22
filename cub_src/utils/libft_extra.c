/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_extra.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 20:31:38 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/22 20:34:22 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

int	stringisdigit(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (true);
	while (s[i])
	{
		if (ft_isdigit(s[i]) == false)
			return (false);
		i++;
	}
	return (true);
}