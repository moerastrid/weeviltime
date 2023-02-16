/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/14 00:52:20 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static void	set_default(t_data *data)
{
	data->mlx = NULL;
	data->wall = NULL;
	data->cam.x = WIDTH / 2;
	data->cam.y = HEIGHT / 2;
	data->map.x = 0;
	data->map.y = 0;
}

int	parse(int argc, char **argv, t_data *data)
{
	int	map_fd;

	(void)argc;
	set_default(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data->mlx)
		return (1);
	map_fd = open(argv[1], O_RDONLY);
	if (!map_fd)
		return (1);
	if (set_data(map_fd, data) == false)
	{
		close(map_fd);
		return (1);
	}
	close(map_fd);
	return (check_map(data));
}
