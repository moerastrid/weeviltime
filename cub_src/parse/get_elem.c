/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_elem.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 19:58:10 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 14:22:40 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static bool	set_plane(t_par *par, char *line, t_eplane n, t_plane *plane)
{
	int		i;
	int		rgb[3];
	char	**temp_arr;

	(void)plane;
	if (par->color_check[n] != true)
	{
		par->color_check[n] = true;
		temp_arr = ft_single_split(&line[2], ',');
		i = 0;
		while (temp_arr[i])
		{
			if (i < 3 && stringisdigit(temp_arr[i]))
				rgb[i] = ft_atoi(temp_arr[i]);
			else
			{
				free (temp_arr);
				return (print_error("wrong color format"));
			}
			i++;
		}
		if (i != 3)
		{
			free (temp_arr);
			return (print_error("wrong color format"));
		}
		plane->color = make_color(rgb[0], rgb[1], rgb[2]);
		free(temp_arr);
		return (true);
	}
	return (false);
}

static bool	init_plane(t_data *data, t_par *par, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		return (set_plane(par, line, C, &data->ceiling));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (set_plane(par, line, F, &data->floor));
	return (false);
}

bool	get_elem(t_data *data, t_par *par, char *temp_line)
{
	if (init_plane(data, par, temp_line) == true)
		return (true);
	//if (init_wall(data, par, temp_line) == true)
	//	return (true);
	return (false);
}
