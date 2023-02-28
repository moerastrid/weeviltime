/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:22:19 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/28 17:07:11 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"


static int	check_tile(t_data *data, t_par *par, int i, int j)
{
	if (i == 0 || i == (data->max.y - 1))
		return (print_error("First or last line"));
	if (j == 0 || par->maparray[i][j + 1] == '\0')
		return (print_error("left or right edge"));
	if (i != 0 && (ft_strlen(par->maparray[i - 1]) < 1
			|| (size_t)j > ft_strlen(par->maparray[i - 1]) - 1))
		return (print_error("Above line too short"));
	if (i != data->max.y - 1 && (ft_strlen(par->maparray[i + 1]) < 1
			|| (size_t)j > ft_strlen(par->maparray[i + 1]) - 1))
		return (print_error("Below line too short"));
	if (par->maparray[i - 1][j] == ' '
		|| par->maparray[i + 1][j] == ' '
		|| par->maparray[i][j - 1] == ' '
		|| par->maparray[i][j + 1] == ' ')
		return (print_error("Bordering character"));
	return (EXIT_SUCCESS);
}

static int	check_spaces(t_data *data, t_par *par)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
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
			else if (par->maparray[i][j] == 'N'
				|| par->maparray[i][j] == 'S'
				|| par->maparray[i][j] == 'W'
				|| par->maparray[i][j] == 'E')
			{
				if (check_tile(data, par, i, j) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				data->player.x = j;
				data->player.y = i;
				data->player.pos.x = (float)j * mapS + (mapS / 4);
				data->player.pos.y = (float)i * mapS + (mapS / 4);
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (EXIT_FAILURE);
	if (par->maparray[data->player.y][data->player.x] == 'N')
		data->player.direction = 90;
	if (par->maparray[data->player.y][data->player.x] == 'S')
		data->player.direction = 270;
	if (par->maparray[data->player.y][data->player.x] == 'W')
		data->player.direction = 180;
	if (par->maparray[data->player.y][data->player.x] == 'E')
		data->player.direction = 0;
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
				return (print_error("NO TABS!!!"));
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
