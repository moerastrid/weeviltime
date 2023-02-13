/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_alloc_split.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 21:33:02 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/14 00:58:04 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	ft_count(char const *s, char c, int *parts, int *cc)
{
	int		i;

	i = 0;
	while (s[i] != 0 && s[i] == c)
	{
		i++;
		(*cc)++;
	}
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			while (s[i] != 0 && s[i] == c)
			{
				i++;
				(*cc)++;
			}
			if (s[i] == 0)
				return ;
			(*parts)++;
		}
		else
			i++;
	}
}

static void	ft_enter_data(void	*startptr, int flen, char const *s, char c)
{
	int		i;
	int		j;
	int		skp;

	i = 0;
	j = 0;
	skp = 0;
	if (s[i] != c)
	{
		((char **)startptr)[j] = &((char *)startptr)[flen];
		j++;
	}
	while (s[i] != 0)
	{
		if (s[i] == c && s[i] == s[i + 1] && s[i + 1] != '\0')
			skp++;
		if (s[i] == c && s[i] != s[i + 1] && s[i + 1] != '\0')
		{
			((char **)startptr)[j] = &((char *)startptr)[i + flen + 1 - skp];
			j++;
		}
		else if (s[i] != c)
			((char *)startptr)[i + flen - skp] = s[i];
		i++;
	}
}

char	**ft_single_split(char const *s, char c)
{
	int		flen;
	int		cc;
	void	*startptr;
	int		parts;

	parts = 1;
	cc = 0;
	ft_count(s, c, &parts, &cc);
	flen = sizeof(char *) * (parts + 1);
	startptr = ft_calloc((flen + ft_strlen(s) - cc + parts), 1);
	if (startptr == 0)
		return (NULL);
	if (*s == '\0')
	{
		((char **)startptr)[0] = NULL;
		return ((char **)startptr);
	}
	ft_enter_data(startptr, flen, s, c);
	return ((char **)startptr);
}
