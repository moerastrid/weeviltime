/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_elem.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 19:58:10 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 16:08:21 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static int	get_wall(t_par *par, char *line, t_wall_e n, t_wall *wall)
{
	int	i;

	i = 0;
	if (par->wall_check[n] != true)
	{
		par->wall_check[n] = true;
		while (line[i] != '\0' && line[i] != '\n')
		{
			if (i < 3 || line[i] == ' ')
				i++;
			else
			{
				if (access(trim_newline(&line[i]), F_OK | R_OK) == -1)
					return (print_error("invalid texture path", -1));
				wall->path = ft_strdup(&line[i]);
				if (wall->path == NULL)
					return (print_error("malloc failure", -1));
				return (1);
			}
		}
	}
	return (-1);
}

static int	init_wall(t_data *data, t_par *par, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (get_wall(par, line, NO, &data->walls[NO]));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (get_wall(par, line, SO, &data->walls[SO]));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (get_wall(par, line, WE, &data->walls[WE]));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (get_wall(par, line, EA, &data->walls[EA]));
	else if (line[0] != '\n')
		return (print_error("non empty line between textures", -1));
	return (0);
}

static int	get_plane(t_par *par, char *line, t_plane_e n, unsigned int	*plane)
{
	int		i;
	int		rgb[3];
	char	**temp_arr;

	if (par->color_check[n] == true)
		return (-1);
	par->color_check[n] = true;
	temp_arr = ft_single_split(&line[2], ',');
	i = 0;
	while (temp_arr[i])
	{
		if (i < 3 && stringisdigit(temp_arr[i]))
		{
			rgb[i] = ft_atoi(temp_arr[i]);
			printf("rgb[%d] : %d\n", i, rgb[i]);
			if (rgb[i] < 0 || rgb[i] > 255)
			{
				free (temp_arr);
				return (-1);
			}
		}
		else
		{
			free (temp_arr);
			return (-1);
		}
		i++;
	}
	free (temp_arr);
	if (i != 3)
		return (-1);
	*plane = make_color(rgb[0], rgb[1], rgb[2]);
	return (1);
}

static int	init_plane(t_data *data, t_par *par, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		return (get_plane(par, line, C, &data->planes[C]));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (get_plane(par, line, F, &data->planes[F]));
	return (0);
}

int	get_elem(t_data *data, t_par *par, char *line)
{
	int	retval;

	retval = init_plane(data, par, line);
	if (retval != 0)
	{
		if (retval == -1)
			print_error("wrong color format", -1);
		return (retval);
	}
	return (init_wall(data, par, line));
}
