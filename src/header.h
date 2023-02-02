/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/02 14:10:36 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/02 16:19:19 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <memory.h>

typedef struct s_player
{
	mlx_instance_t	*instance;
}	t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	t_player		player;
	// t_wall			wall;
	// t_list			*map_lines;
	char			**map_array;
}	t_data;
