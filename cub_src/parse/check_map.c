/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:22:19 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/09 15:01:59 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static int	check_tile(t_data *data, t_par *par, int i, int j)
{
	if (i == 0 || i == (data->max.y - 1))
		return (print_error("First or last line", EXIT_FAILURE));
	if (j == 0 || par->maparray[i][j + 1] == '\0')
		return (print_error("left or right edge", EXIT_FAILURE));
	if (i != 0 && (ft_strlen(par->maparray[i - 1]) < 1
			|| (size_t)j > ft_strlen(par->maparray[i - 1]) - 1))
		return (print_error("Above line too short", EXIT_FAILURE));
	if (i != data->max.y - 1 && (ft_strlen(par->maparray[i + 1]) < 1
			|| (size_t)j > ft_strlen(par->maparray[i + 1]) - 1))
		return (print_error("Below line too short", EXIT_FAILURE));
	if (par->maparray[i - 1][j] == ' '
		|| par->maparray[i + 1][j] == ' '
		|| par->maparray[i][j - 1] == ' '
		|| par->maparray[i][j + 1] == ' ')
		return (print_error("Bordering character", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	set_player(t_data *data, t_par *par, int i, int j)
{
	char		c;
	static int	player_count = 0;

	c = par->maparray[i][j];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		player_count += 1;
		if (check_tile(data, par, i, j) == EXIT_FAILURE || player_count > 1)
			return (print_error("set_player error", EXIT_FAILURE));
		data->player.x = j + 0.5;
		data->player.y = i + 0.5;
	}
	if (c == 'N')
		data->player.angle = 90;
	if (c == 'S')
		data->player.angle = 270;
	if (c == 'W')
		data->player.angle = 180;
	if (c == 'E')
		data->player.angle = 0;
	data->player.dirx = cos(deg_to_rad(data->player.angle));
	data->player.diry = -sin(deg_to_rad(data->player.angle));
	data->player.lrx = cos(deg_to_rad(fix_ang(data->player.angle + 90.0)));
	data->player.lry = -sin(deg_to_rad(fix_ang(data->player.angle + 90.0)));
	return (EXIT_SUCCESS);
}

static int	check_spaces(t_data *data, t_par *par)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = -1;
	while (i < data->max.y)
	{
		j = 0;
		while (par->maparray[i][j] != '\0')
		{
			if (par->maparray[i][j] == '0')
			{
				if (check_tile(data, par, i, j) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			if (set_player(data, par, i, j))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	check_tabs(t_data *data, t_par *par)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->max.y)
	{
		j = 0;
		while (par->maparray[i][j] != '\0')
		{
			if (par->maparray[i][j] == '\t')
				return (print_error("NO TABS!!!", EXIT_FAILURE));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_map(t_data *data, t_par *par)
{
	if (check_tabs(data, par) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_spaces(data, par) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
