/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_extra.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 20:31:38 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 17:28:34 by ageels        ########   odam.nl         */
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
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == true)
			digit = true;
		else
			break ;
		i++;
	}
	while (s[i] == ' ')
		i++;
	if (s[i] != '\0' && s[i] != '\n')
		return (false);
	return (digit);
}

char	*trim_newline(char *s)
{
	int		i;
	char	*trimmed;

	trimmed = s;
	i = 0;
	while (trimmed[i] != '\0')
	{
		if (trimmed[i] == '\n')
			trimmed[i] = '\0';
		i++;
	}
	return (trimmed);
}
