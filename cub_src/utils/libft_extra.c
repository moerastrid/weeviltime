/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_extra.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 20:31:38 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 14:15:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

bool	stringisdigit(char *s)
{
	int		i;
	bool	digit;

	i = 0;
	digit = false;
	if (!s)
		return (true);
	while (s[i])
	{
		if (ft_isdigit(s[i]) == false && s[i] != ' ')
			return (false);
		if (ft_isdigit(s[i]) == true)
			digit = true;
		i++;
	}
	return (digit);
}
