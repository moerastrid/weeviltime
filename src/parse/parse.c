/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/08 11:22:17 by mforstho      ########   odam.nl         */
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

int	save_map(int map, t_data *data, char *line)
{
	int		map_size;
	char	*temp_line;

	map_size = 0;
	if (map < 0)
		return (EXIT_FAILURE);
	data->map_lines = NULL;
	temp_line = line;
	while (temp_line != NULL)
	{
		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
		{
			ft_lstclear(&data->map_lines, &free);
			free(temp_line);
			return (EXIT_FAILURE);
		}
		temp_line = get_next_line(map);
		map_size++;
	}
	if (map_size < 1)
		return (EXIT_FAILURE);
	data->map_size = map_size;
	return (EXIT_SUCCESS);
}

void	save_wall(t_data *data, mlx_image_t *wall, char *line, char *param)
{
	wall = mlx_texture_to_image(data->mlx,
			mlx_load_png(ft_strtrim(line, param)));
}

void	free_map_array(char **map_array)
{
	int	y;

	if (map_array == NULL)
		return ;
	y = 0;
	while (map_array[y] != NULL)
	{
		free(map_array[y]);
		y++;
	}
	free(map_array);
}

int	convert_map(t_data *data)
{
	int		rows;
	int		y;
	char	**map_array;
	t_list	*map_lines;

	map_lines = data->map_lines;
	rows = ft_lstsize(map_lines);
	map_array = malloc(((size_t)rows + 1) * sizeof(char *));
	if (map_array == NULL)
		return (EXIT_FAILURE);
	y = 0;
	while (y < rows)
	{
		map_array[y] = strdup(map_lines->content);
		if (map_array[y] == NULL)
		{
			free_map_array(map_array);
			return (EXIT_FAILURE);
		}
		map_lines = map_lines->next;
		y++;
	}
	map_array[y] = NULL;
	data->map_array = map_array;
	return (EXIT_SUCCESS);
}

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_size)
	{
		printf("%s", data->map_array[i]);
		i++;
	}
}

int	init_map_data(int map, t_data *data)		//initialiseert de ceiling en floor kleuren + koppelt png bestanden aan de individuele muur-kanten
{
	char	*temp_line;
	char	**temp_arr;

	temp_line = get_next_line(map);
	while (temp_line != NULL)
	{
		if (ft_strncmp(temp_line, "NO", 2) == 0)
			save_wall(data, data->walls.wall_north, temp_line, "NO ./\n");
		else if (ft_strncmp(temp_line, "SO", 2) == 0)
			save_wall(data, data->walls.wall_south, temp_line, "SO ./\n");
		else if (ft_strncmp(temp_line, "WE", 2) == 0)
			save_wall(data, data->walls.wall_west, temp_line, "WE ./\n");
		else if (ft_strncmp(temp_line, "EA", 2) == 0)
			save_wall(data, data->walls.wall_east, temp_line, "EA ./\n");
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
