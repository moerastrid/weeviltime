/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 19:00:17 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 18:05:23 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

/*
	sets default values & allocates memory (if possible)
	first general data, then parse data.
*/
static int	set_default_values(t_data *data, t_par *par)
{
	data->mlx = NULL;
	data->max.x = 0;
	data->max.y = 0;
	data->walls = ft_calloc(4, sizeof(t_wall));
	if (data->walls == NULL)
		return (print_error("malloc error"));
	data->planes = ft_calloc(2, sizeof(t_plane));
	if (data->planes == NULL)
		return (print_error("malloc error"));
	par->maplst = NULL;
	par->maparray = NULL;
	par->wall_check = ft_calloc(4, sizeof(bool));
	if (par->wall_check == NULL)
		return (print_error("malloc error"));
	par->color_check = ft_calloc(2, sizeof(bool));
	if (par->color_check == NULL)
		return (print_error("malloc error"));
	return (EXIT_SUCCESS);
}

static int	check_arguments(int argc, char **argv, t_par *parse_data)
{
	int		len;

	if (argc <= 1)
		return (print_error("Need map"));
	if (ft_strlen(argv[1]) <= ft_strlen(".cub"))
		return (print_error("invalid map name"));
	len = ft_strlen(argv[1]);
	if (argv[1][len - 1] != 'b' || argv[1][len - 2] != 'u' \
		|| argv[1][len - 3] != 'c' || argv[1][len - 4] != '.')
		return (print_error("invalid map name"));
	parse_data->fd_cub = open(argv[1], O_RDONLY);
	if (parse_data->fd_cub < 0)
		return (print_error("map no access"));
	return (EXIT_SUCCESS);
}

int	parse(int argc, char **argv, t_data *data)
{
	t_par	parse_data;

	if (check_arguments(argc, argv, &parse_data))
		return (EXIT_FAILURE);
	if (set_default_values(data, &parse_data))
	{
		free_par(&parse_data);
		return (EXIT_FAILURE);
	}
	if (get_data(data, &parse_data))
	{
		free_par(&parse_data);
		return (EXIT_FAILURE);
	}
	compatibalize_map(data, &parse_data);
	free_par(&parse_data);
	return (EXIT_SUCCESS);
}
