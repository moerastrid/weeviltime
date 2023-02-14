/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/14 17:12:07 by mforstho      ########   odam.nl         */
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

bool	save_wall(t_data *data, mlx_image_t *wall, char *line)
{
	mlx_texture_t	*texture;

	(void)wall;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	texture = mlx_load_png(&line[3]);
	if (texture == NULL)
		return (false);
	wall = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	return (true);
}

bool	set_walls(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (save_wall(data, data->walls.wall_north, line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (save_wall(data, data->walls.wall_south, line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (save_wall(data, data->walls.wall_west, line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (save_wall(data, data->walls.wall_east, line));
	else
		return (false);
	return (true);
}

bool	cf_check(t_data *data, char *line)
{
	char	**temp_arr;

	if (ft_strncmp(line, "C ", 2) == 0)		// lengte van temp array checken voor beiden
	{
		temp_arr = ft_split(&line[2], ',');
		data->sky.color = make_color(ft_atoi(temp_arr[0]),
				ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
		free_array(temp_arr);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		temp_arr = ft_split(&line[2], ',');
		data->floor.color = make_color(ft_atoi(temp_arr[0]),
				ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
		free_array(temp_arr);
	}
	else
		return (false);
	return (true);
}

int	init_map_data(int map, t_data *data)		//initialiseert de ceiling en floor kleuren + koppelt png bestanden aan de individuele muur-kanten
{
	char	*temp_line;
	int		element_count;

	temp_line = get_next_line(map);
	element_count = 0;
	while (temp_line != NULL)
	{
		if (element_count < 6)
		{
			if (set_walls(data, temp_line) || cf_check(data, temp_line))
				element_count++;
			free(temp_line);
		}
		else
		{
			save_map(map, data, temp_line);
			convert_map(data);
			ft_lstclear(&data->map_lines, &free);
			if (check_map_tabs(data) == EXIT_FAILURE
				|| check_map_spaces(data) == EXIT_FAILURE)
			{
				free_array(data->map_array);
				return (EXIT_FAILURE);
			}
			print_map(data);		// Kan je aan en uit zetten
		}
		temp_line = get_next_line(map);
	}
	if (element_count != 6)
	{
		printf("Missing color/texture arguments\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
