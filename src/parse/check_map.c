/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 15:22:19 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/28 17:02:45 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	check_all(t_data *data, int i, int j)
{
	if (i == 0 || i == (data->map_y - 1))
		return (print_error("First or last line"));
	if (j == 0 || data->map_array[i][j + 1] == '\0')
		return (print_error("left or right edge"));
	if (i != 0 && (ft_strlen(data->map_array[i - 1]) < 1
			|| (size_t)j > ft_strlen(data->map_array[i - 1]) - 1))
		return (print_error("Above line too short"));
	if (i != data->map_y - 1 && (ft_strlen(data->map_array[i + 1]) < 1
			|| (size_t)j > ft_strlen(data->map_array[i + 1]) - 1))
		return (print_error("Below line too short"));
	if (data->map_array[i - 1][j] == ' '
		|| data->map_array[i + 1][j] == ' '
		|| data->map_array[i][j - 1] == ' '
		|| data->map_array[i][j + 1] == ' ')
		return (print_error("Bordering character"));
	return (EXIT_SUCCESS);
}

static int	check_map_spaces(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < data->map_y)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == '0')
			{
				if (check_all(data, i, j) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (data->map_array[i][j] == 'N'
				|| data->map_array[i][j] == 'S'
				|| data->map_array[i][j] == 'W'
				|| data->map_array[i][j] == 'E')
			{
				if (check_all(data, i, j) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				data->player.x = j;
				data->player.y = i;
				data->player.pos_x = ((float)j * mapS) + ((mapS / 2) - (mapS / 8));
				data->player.pos_y = ((float)i * mapS) + ((mapS / 2) - (mapS / 8));
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (EXIT_FAILURE);
	if (data->map_array[data->player.y][data->player.x] == 'N')
		data->player.direction = 90;
	if (data->map_array[data->player.y][data->player.x] == 'S')
		data->player.direction = 270;
	if (data->map_array[data->player.y][data->player.x] == 'W')
		data->player.direction = 180;
	if (data->map_array[data->player.y][data->player.x] == 'E')
		data->player.direction = 0;
	return (EXIT_SUCCESS);
}

static int	check_map_tabs(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_y)
	{
		j = 0;
		while (data->map_array[i][j] != '\0')
		{
			if (data->map_array[i][j] == '\t')
				return (print_error("NO TABS!!!"));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_map(t_data *data)
{
	if (check_map_tabs(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map_spaces(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}



// static int	check_every_zero(t_data *data, int i, int j)
// {
// 	if (i == 0 || i == (data->map_y - 1))
// 		return (print_error("First or last line"));
// 	if (j == 0 || data->map_array[i][j + 1] == '\0')
// 		return (print_error("left or right edge"));
// 	if (i != 0 && (ft_strlen(data->map_array[i - 1]) < 1
// 			|| (size_t)j > ft_strlen(data->map_array[i - 1]) - 1))
// 		return (print_error("Above line too short"));
// 	if (i != data->map_y - 1 && (ft_strlen(data->map_array[i + 1]) < 1
// 			|| (size_t)j > ft_strlen(data->map_array[i + 1]) - 1))
// 		return (print_error("Below line too short"));
// 	if (data->map_array[i - 1][j] == ' '
// 		|| data->map_array[i + 1][j] == ' '
// 		|| data->map_array[i][j - 1] == ' '
// 		|| data->map_array[i][j + 1] == ' ')
// 		return (print_error("Bordering character"));
// 	return (EXIT_SUCCESS);
// }

// static int	check_map_spaces(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < data->map_y)
// 	{
// 		j = 0;
// 		while (data->map_array[i][j] != '\0')
// 		{
// 			if (data->map_array[i][j] == '0')
// 			{
// 				if (check_every_zero(data, i, j) == EXIT_FAILURE)
// 					return (EXIT_FAILURE);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

// static int	check_map_tabs(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < data->map_y)
// 	{
// 		j = 0;
// 		while (data->map_array[i][j] != '\0')
// 		{
// 			if (data->map_array[i][j] == '\t')
// 				return (print_error("NO TABS!!!"));
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	check_map(t_data *data)
// {
// 	if (check_map_tabs(data) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (check_map_spaces(data) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }
