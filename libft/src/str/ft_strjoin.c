/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:21:52 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/14 00:15:45 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// EDIT ASTRID : protected your strjoin for segfaults :)

// Allocates sufficient memory to new string
// Adds s1 and s2 together in the new string

#include "libft.h"

char	*combine(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*comb;

	i = 0;
	j = 0;
	comb = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (comb == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		comb[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		comb[i] = s2[j];
		i++;
		j++;
	}
	comb[i] = '\0';
	return (comb);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	else
		return (combine(s1, s2));
}
