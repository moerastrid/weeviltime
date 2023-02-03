/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 18:13:11 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	set_default_values(t_data *data)
{
	data->mlx = NULL;
	data->wall = NULL;
	data->camx = WIDTH / 2;
	data->camy = HEIGHT / 2;
}

int	parse(int argc, char **argv, t_data *data)
{
	set_default_values(data);
	(void)argc;
	(void)argv;
	return (0);
}

int	init_map_data(int map, t_data *data)		//initialiseert de ceiling en floor kleuren + koppelt png bestanden aan de individuele muur-kanten
{
	char	*temp_line;
	char	**temp_arr;

	temp_line = get_next_line(map);
	while (temp_line != NULL)
	{
		if (ft_strncmp(temp_line, "NO", 2) == 0)
			data->walls.wall_north = mlx_texture_to_image(data->mlx,
					mlx_load_png(ft_strtrim(temp_line, "NO ./\n")));
		else if (ft_strncmp(temp_line, "SO", 2) == 0)
			data->walls.wall_south = mlx_texture_to_image(data->mlx,
					mlx_load_png(ft_strtrim(temp_line, "SO ./\n")));
		else if (ft_strncmp(temp_line, "WE", 2) == 0)
			data->walls.wall_west = mlx_texture_to_image(data->mlx,
					mlx_load_png(ft_strtrim(temp_line, "WE ./\n")));
		else if (ft_strncmp(temp_line, "EA", 2) == 0)
			data->walls.wall_east = mlx_texture_to_image(data->mlx,
					mlx_load_png(ft_strtrim(temp_line, "EA ./\n")));
		else if (ft_strncmp(temp_line, "C", 1) == 0)
		{
			temp_arr = ft_split(ft_strtrim(temp_line, "C "), ',');
			data->sky.color = make_color(ft_atoi(temp_arr[0]),
					ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
		}
		else if (ft_strncmp(temp_line, "F", 1) == 0)
		{
			temp_arr = ft_split(ft_strtrim(temp_line, "F "), ',');
			data->floor.color = make_color(ft_atoi(temp_arr[0]),
					ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
		}
		temp_line = get_next_line(map);
	}
	return (0);
}

// int	save_map(int map, t_data *data)
// {
// 	int		map_size;
// 	char	*temp_line;

// 	map_size = 0;
// 	if (map < 0)
// 		return (EXIT_FAILURE);
// 	data->map_lines = NULL;
// 	temp_line = get_next_line(map);
// 	while (temp_line != NULL)
// 	{
// 		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
// 		{
// 			ft_lstclear(&data->map_lines, &free);
// 			free(temp_line);
// 			return (EXIT_FAILURE);
// 		}
// 		temp_line = get_next_line(map);
// 		map_size++;
// 	}
// 	if (map_size < 1)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }
