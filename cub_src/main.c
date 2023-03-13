/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:33 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 16:46:16 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_include/cub.h"

int	set_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->walls[i].texture = mlx_load_png(data->walls[i].path);
		if (data->walls[i].texture == NULL)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	delete_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_delete_texture(data->walls[i].texture);
		i++;
	}
}

static void	leakfunc(void)
{
	system("leaks -q cub3D");
}

int32_t	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	ft_bzero(&data, sizeof(t_data));
	if (parse(argc, argv, &data))
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	set_textures(&data);
	ret = graphics(&data);
	delete_textures(&data);
	free_data(&data);
	return (ret);
}
