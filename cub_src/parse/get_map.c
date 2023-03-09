/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 17:46:24 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/09 13:48:59 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static int	convert_map(t_data *data, t_par *par)
{
	int		i;
	t_list	*lst;

	lst = par->maplst;
	par->maparray = ft_calloc(((size_t)data->max.y + 1), sizeof(char *));
	if (!par->maparray)
		return (print_error("malloc error", EXIT_FAILURE));
	i = 0;
	while (i < data->max.y)
	{
		par->maparray[i] = strdup(lst->content);
		if (par->maparray[i] == NULL)
			return (print_error("malloc error", EXIT_FAILURE));
		lst = lst->next;
		i++;
	}
	par->maparray[i] = NULL;
	return (EXIT_SUCCESS);
}

static void	save_max_length(t_data *data, char *line)
{
	int	length;

	length = ft_strlen(line);
	if (data->max.x < length)
		data->max.x = length;
	data->max.y++;
}

static char	*skip_empty_line(t_par *par, char *line)
{
	char	*temp_line;

	temp_line = ft_strdup(line);
	free(line);
	while (temp_line != NULL && temp_line[0] == '\n')
	{
		free(temp_line);
		temp_line = get_next_line(par->fd_cub);
	}
	return (temp_line);
}

int	get_map(t_data *data, t_par *par, char *line)
{
	char	*temp;

	temp = skip_empty_line(par, line);
	while (temp != NULL)
	{
		if (temp[0] == '\n')
			break ;
		if (temp[ft_strlen(temp) - 1] == '\n')
			temp[ft_strlen(temp) - 1] = '\0';
		if (ft_lstnew_back(&par->maplst, temp) == NULL)
		{
			ft_lstclear(&par->maplst, &free);
			free(temp);
			return (print_error("ft_lstnew_back error", EXIT_FAILURE));
		}
		save_max_length(data, temp);
		temp = get_next_line(par->fd_cub);
	}
	temp = skip_empty_line(par, temp);
	if (temp != NULL || data->max.y < 1)
	{
		free(temp);
		return (print_error("can only have one map", EXIT_FAILURE));
	}
	return (convert_map(data, par));
}
