/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/13 11:24:11 by mforstho      ########   odam.nl         */
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

void	save_wall(t_data *data, mlx_image_t *wall, char *line, char *param)
{
	(void)wall;
	wall = mlx_texture_to_image(data->mlx,
			mlx_load_png(ft_strtrim(line, param)));
}

void	set_walls(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		save_wall(data, data->walls.wall_north, line, "NO ./\n");
	else if (ft_strncmp(line, "SO", 2) == 0)
		save_wall(data, data->walls.wall_south, line, "SO ./\n");
	else if (ft_strncmp(line, "WE", 2) == 0)
		save_wall(data, data->walls.wall_west, line, "WE ./\n");
	else if (ft_strncmp(line, "EA", 2) == 0)
		save_wall(data, data->walls.wall_east, line, "EA ./\n");
}

void	cf_check(t_data *data, char *line)
{
	char	**temp_arr;

	if (ft_strncmp(line, "C", 1) == 0)
	{
		temp_arr = ft_split(ft_strtrim(line, "C "), ',');
		data->sky.color = make_color(ft_atoi(temp_arr[0]),
				ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		temp_arr = ft_split(ft_strtrim(line, "F "), ',');
		data->floor.color = make_color(ft_atoi(temp_arr[0]),
				ft_atoi(temp_arr[1]), ft_atoi(temp_arr[2]));
	}
}

int	init_map_data(int map, t_data *data)		//initialiseert de ceiling en floor kleuren + koppelt png bestanden aan de individuele muur-kanten
{
	char	*temp_line;

	temp_line = get_next_line(map);
	while (temp_line != NULL)
	{
		set_walls(data, temp_line);
		cf_check(data, temp_line);
		if (ft_strtrim(temp_line, " ")[0] == '1')
		{
			save_map(map, data, temp_line);
			convert_map(data);
			// print_map(data);		// Kan je aan en uit zetten
			check_map_tabs(data);
			check_map_spaces(data);
		}
		temp_line = get_next_line(map);
	}
	return (0);
}
