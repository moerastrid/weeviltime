/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 18:00:07 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 16:09:27 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static bool	set_texture(t_data *data, mlx_image_t *wall, char *line, char *par)
{
	mlx_texture_t	*texture;
	char			*s;

	s = ft_strtrim(line, par);
	if (!s)
		return (false);
	texture = mlx_load_png(s);
	if (!texture)
		return (false);
	wall = mlx_texture_to_image(data->mlx, texture);
	free(s);
	mlx_delete_texture(texture);
	return (true);
}

static bool	set_walls(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (set_texture(data, data->walls.wall_north, line, "NO ./\n"));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (set_texture(data, data->walls.wall_south, line, "SO ./\n"));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (set_texture(data, data->walls.wall_west, line, "WE ./\n"));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (set_texture(data, data->walls.wall_east, line, "EA ./\n"));
	return (false);
}

static bool	set_cf(t_data *data, char *line)
{
	char	**arr;
	char	*s;

	arr = NULL;
	s = NULL;

	if (ft_strncmp(line, "C", 1) == 0)
	{
		s = ft_strtrim(line, "C ");
		arr = ft_single_split(s, ',');
		data->sky.color = make_color(ft_atoi(arr[0]), \
			ft_atoi(arr[1]), ft_atoi(arr[2]));
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		s = ft_strtrim(line, "F ");
		arr = ft_single_split(s, ',');
		data->floor.color = make_color(ft_atoi(arr[0]), \
			ft_atoi(arr[1]), ft_atoi(arr[2]));
	}
	else
		return (false);
	free(s);
	free(arr);
	return (true);
}

// initialiseert de ceiling en floor kleuren 
// + koppelt png bestanden aan de individuele muur-kanten
bool	set_data(int map_fd, t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	(void)data;
	line = get_next_line(map_fd);
	while (line != NULL)
	{
		if (i < 4 && set_walls(data, line) == true)
			i++;
		else if (i == 4 || ((i == 5 || i == 6) && set_cf(data, line) == true) \
			|| i == 7)
			i++;
		else if (i > 7)
			return (set_map(data, line, map_fd));
		else
		{
			free(line);
			printf("ERROR\n");
			return (false);
		}
		free(line);
		line = get_next_line(map_fd);
	}
	return (false);
}
