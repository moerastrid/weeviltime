/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 19:00:17 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/27 20:39:46 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static int	set_default_values(t_data *data, t_par *par)
{
	// general data:
	data->mlx = NULL;
	data->par = par;
	data->max.x = 0;
	data->max.y = 0;
	data->walls = ft_calloc(4, sizeof(t_wall));
	if (data->walls == NULL)
		return (print_error("malloc error"));
	data->planes = ft_calloc(2, sizeof(t_plane));
	if (data->planes == NULL)
	{
		free(data->walls);
		return (print_error("malloc error"));
	}
	// parse data:
	par->map_lst = NULL;
	par->wall_check = ft_calloc(4, sizeof(bool));
	if (par->wall_check == NULL)
	{
		free(data->walls);
		free(data->planes);
		return (print_error("malloc error"));
	}
	par->color_check = ft_calloc(2, sizeof(bool));
	if (par->color_check == NULL)
	{
		free(data->walls);
		free(data->planes);
		free(par->wall_check);
		return (print_error("malloc error"));
	}
	return (EXIT_SUCCESS);
}

static void	clean_par(t_par *par)
{
	t_list	*nxt;

	while (par->map_lst != NULL)
	{
		nxt = par->map_lst->next;
		free (par->map_lst);
		par->map_lst = nxt;
	}
	free(par->wall_check);
	free(par->color_check);
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
		return (EXIT_FAILURE);
	if (get_data(data, &parse_data))
	{
		clean_par(&parse_data);
		return (EXIT_FAILURE);
	}
	clean_par(&parse_data);
	return (EXIT_SUCCESS);
}
