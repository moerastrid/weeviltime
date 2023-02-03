/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/03 13:46:55 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	parse(int argc, char **argv, t_data *data)
{
	data->mlx = NULL;
	data->wall = NULL;
	data->sky.color = SKYCOLOR;
	data->floor.color = FLOORCOLOR;
	(void)argc;
	(void)argv;
	return (0);
}

// void	save_map_tmp(int map, t_data *data)
// {
// 	int		map_size;
// 	char	*temp_line;

// 	map_size = 0;
// 	if (map < 0)
// 		return ;
// 	data->map_lines = NULL;
// 	temp_line = get_next_line(map);
// 	while (temp_line != NULL)
// 	{
// 		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
// 		{
// 			ft_lstclear(&data->map_lines, &free);
// 			free(temp_line);
// 			return (set_error(MALLOC_ERROR));
// 		}
// 		temp_line = get_next_line(map);
// 		map_size++;
// 	}
// 	if (map_size < 1)
// 		return (set_error(SMALL_MAP_ERROR));
// 	return (OK);
// }

int	init_map_data(int map, t_data *data)
{
	char	*temp_line;

	temp_line = get_next_line(map);
	data->wall_textures = malloc(sizeof(char *) * 4);
	data->f_c_color = malloc(sizeof(char *) * 2);
	while (temp_line != NULL)
	{
		ft_strlcpy(data->wall_textures[0], "test", 4);
		if (ft_strncmp(temp_line, "NO", 2) == 0)
			ft_strlcpy(data->wall_textures[0], temp_line, ft_strlen(temp_line));
		else if (ft_strncmp(temp_line, "SO", 2) == 0)
			ft_strlcpy(data->wall_textures[1], temp_line, ft_strlen(temp_line));
		else if (ft_strncmp(temp_line, "WE", 2) == 0)
			ft_strlcpy(data->wall_textures[2], temp_line, ft_strlen(temp_line));
		else if (ft_strncmp(temp_line, "EA", 2) == 0)
			ft_strlcpy(data->wall_textures[3], temp_line, ft_strlen(temp_line));
		else if (ft_strncmp(temp_line, "C", 1) == 0)
			ft_strlcpy(data->f_c_color[0], temp_line, ft_strlen(temp_line));
		else if (ft_strncmp(temp_line, "F", 1) == 0)
			ft_strlcpy(data->f_c_color[1], temp_line, ft_strlen(temp_line));
		temp_line = get_next_line(map);
	}
	printf("%s\n", data->wall_textures[0]);
	printf("%s\n", data->wall_textures[1]);
	printf("%s\n", data->wall_textures[2]);
	printf("%s\n", data->wall_textures[3]);
	printf("%s\n", data->f_c_color[0]);
	printf("%s\n", data->f_c_color[1]);
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
