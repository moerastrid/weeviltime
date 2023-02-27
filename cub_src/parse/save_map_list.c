/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 17:46:24 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 20:42:16 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static void	save_max_length(t_data *data, char *line)
{
	int	length;

	length = ft_strlen(line);
	if (data->max.x < length)
		data->max.x = length;
	data->max.y++;
}

char	*skip_empty_line(t_par *par, char *line)
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

static bool	save_line(t_par *par, char *line)
{
	t_list	*new;

	new = ft_lstnew(line);
	if (new == NULL)
		return (false);
	if (par->map_lst == NULL)
		par->map_lst = new;
	else
		ft_lstlast(par->map_lst)->next = new;
	return (true);
}

int	save_map_list(t_data *data, t_par *par, char *line)
{
	char	*temp;

	temp = skip_empty_line(par, line);
	while (temp != NULL)
	{
		if (temp[0] == '\n')
			break ;
		if (temp[ft_strlen(temp) - 1] == '\n')
			temp[ft_strlen(temp) - 1] = '\0';
		if (save_line(par, temp) == false)
			return (EXIT_FAILURE);
		save_max_length(data, temp);
		free(temp);
		temp = get_next_line(par->fd_cub);
	}
	temp = skip_empty_line(par, temp);
	if (temp != NULL || data->max.y < 1)
	{
		free(temp);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
