/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/28 20:50:36 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_include/cub.h"

static void	leakfunc(void)
{
	system("leaks -q cub3D");
}

int32_t	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	ft_bzero(&data, sizeof(t_data));
	atexit(leakfunc);
	if (parse(argc, argv, &data))
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	ret = gameloop(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
