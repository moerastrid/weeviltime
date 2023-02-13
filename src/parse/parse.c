/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/13 18:35:31 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	parse(int argc, char **argv, t_data *data)
{
	int	map_fd;
	(void)argc;
	set_default_values(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
	if (!data->mlx)
		return (1);
	map_fd = open(argv[1], O_RDONLY);
	if (!map_fd)
		return (1);
	set_map_data(map_fd, data);
	// wat als deze open een error code geeft?
	return (0);
}
