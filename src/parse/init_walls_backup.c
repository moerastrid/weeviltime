/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_walls_backup.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 13:53:23 by mforstho      #+#    #+#                 */
/*   Updated: 2023/02/19 22:52:08 by astrid        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/header.h"

// static bool	save_wall(t_data *data, mlx_image_t *wall, char *line)
// {
// 	mlx_texture_t	*texture;

// 	// (void)wall;
// 	if (line[ft_strlen(line) - 1] == '\n')
// 		line[ft_strlen(line) - 1] = '\0';
// 	texture = mlx_load_png(&line[3]);
// 	if (texture == NULL)
// 		return (false);
// 	printf("Test\n");
// 	wall = mlx_texture_to_image(data->mlx, texture);
// 	if (wall == NULL)
// 	{
// 		return (false);
// 	}
// 	mlx_delete_texture(texture);
// 	return (true);
// }


/*
static bool	set_wall(t_data *data, char *line, int n, mlx_image_t *wall)
{
	mlx_texture_t	*texture;
	if (data->wall_check[n] != true)
	{
		data->wall_check[n] = true;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		texture = mlx_load_png(&line[3]);
		if (texture == NULL)
			return (false);
		printf("Test\n");
		wall = mlx_texture_to_image(data->mlx, texture);
		if (wall == NULL)
			return (false);
		mlx_delete_texture(texture);
		return (true);
	}
	return (false);		// moet dit reworken om de juiste error te geven
}
bool	init_walls(t_data *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_wall(data, line, EA, data->walls.wall_east));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_wall(data, line, NO, data->walls.wall_north));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_wall(data, line, WE, data->walls.wall_west));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_wall(data, line, SO, data->walls.wall_south));
	return (false);
}
*/


/*
static bool	save_wall(t_data *data, mlx_image_t *wall, char *line)
{
	mlx_texture_t	*texture;
	// (void)wall;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	texture = mlx_load_png(&line[3]);
	if (texture == NULL)
		return (false);
	printf("Test\n");
	wall = mlx_texture_to_image(data->mlx, texture);
	if (wall == NULL)
	{
		return (false);
	}
	mlx_delete_texture(texture);
	return (true);
}
static bool	set_wall(t_data *data, char *line, int n, mlx_image_t *wall)
{
	if (data->wall_check[n] != true)
	{
		data->wall_check[n] = true;
		return (save_wall(data, wall, line));
	}
	return (false);		// moet dit reworken om de juiste error te geven
}
*/