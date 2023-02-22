/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 20:36:31 by ageels        #+#    #+#                 */
/*   Updated: 2023/02/22 20:45:20 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

# ifndef WIDTH
#  define WIDTH 400
# endif
# ifndef HEIGHT
#  define HEIGHT 400
# endif

typedef enum e_eplane
{
	C,
	F,
}		t_eplane;

typedef struct s_par
{
	int		fd_cub;
	bool	*wall_check;
	bool	*color_check;
}		t_par;

typedef struct s_plane
{
	//mlx_image_t		*img;
	unsigned int	color;
}	t_plane;

typedef struct s_data
{
	t_par	*par;
	mlx_t	*mlx;
	t_plane	ceiling;
	t_plane	floor;
}		t_data;

#endif