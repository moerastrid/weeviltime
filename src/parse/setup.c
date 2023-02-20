/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 16:49:05 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/20 12:50:01 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	set_default_values(t_data *data)
{
	data->mlx = NULL;
	data->wall = NULL;
	data->cam.x = WIDTH / 2;
	data->cam.y = HEIGHT / 2;
}

int	setup(int argc, char **argv, t_data *data)
{
	set_default_values(data);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

// static void	set_default_values(t_data *data, t_par *pars)
// {
// 	(void)pars;
// 	data->mlx = NULL;
// 	data->wall = NULL;
// 	data->cam.x = WIDTH / 2;
// 	data->cam.y = HEIGHT / 2;
// }

// int	setup(int argc, char **argv, t_data *data)
// {
// 	t_par	pars;

// 	if (argc <= 1)
// 	{
// 		printf("Need map\n");
// 		return (EXIT_FAILURE);
// 	}
// 	set_default_values(data, &pars);
// 	data->mlx = mlx_init(WIDTH, HEIGHT, "~Weevil time~", false);
// 	if (!data->mlx)
// 		return (EXIT_FAILURE);
// 	pars.fd = open(argv[1], O_RDONLY);
// 	if (!pars.fd)
// 		return (EXIT_FAILURE);
// 	if (init_map(data, &pars) == EXIT_FAILURE)
// 	{
// 		mlx_terminate(data->mlx);
// 		return (EXIT_FAILURE);
// 	}
// 	close(pars.fd);
// 	return (EXIT_SUCCESS);
// }
