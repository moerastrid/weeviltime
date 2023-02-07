/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/06 16:26:29 by mforstho      ########   odam.nl         */
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

// int	init_map_layout(int map)
// {
// 	char	*temp_line;

// 	temp_line = get_next_line(map);
// 	while (temp_line != NULL)
// 	{
// 		if (ft_strtrim(temp_line, " ")[0] != '1' && ft_strtrim(temp_line, " ")[ft_strlen(temp_line)] != '1')
// 			printf("Map error\n");
// 		else
// 			printf("Map ok\n");
// 		temp_line = get_next_line(map);
// 	}
// 	return (EXIT_SUCCESS);
// }

// static int	horizontal_edge(char *map_line, size_t line_length)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i != (line_length - 1))
// 	{
// 		if (map_line[i] != '1')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

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
	while (i < 14)
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
			print_map(data);
			if (check_map_edge(data) != EXIT_SUCCESS)
				printf("\nMap edge error\n");
			if (check_map_spaces(data) != EXIT_SUCCESS)
				printf("Map space error\n");
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
