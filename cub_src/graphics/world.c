/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 18:53:25 by mforstho      #+#    #+#                 */
/*   Updated: 2023/03/13 14:50:03 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub_include/cub.h"

unsigned int	find_color(int side)
{
	unsigned int	color;

	color = 0xFFFFFFFF;
	if (side == NO)
		color = 0xBB2222FF;
	if (side == SO)
		color = 0xBBBB22FF;
	if (side == WE)
		color = 0x2222BBFF;
	if (side == EA)
		color = 0x22BBBBFF;
	return (color);
}

/*
horizontal_wall_place and vertical_wall_place are the location of the pixel on the wall
divided on a scale from 0 to 1
so we can use it to read the correct pixel from the texture :)

PROBLEEM : hij maakt way te veel images als je het zo doet en loopt dan helemaal vast haha wat stom
*/

void	draw_wall_line(t_data *data, t_ray *ray, float angle, float dist)
{
	float			p;
	float			height;
	int				offset;
	int				hor_hitp;
	int				ver_hitp;
	unsigned int	color;
	int				i;
	mlx_texture_t	*t;
	//mlx_image_t		*temp;

	t = data->walls[ray->side].texture;
	hor_hitp = 0;
	p = dist * cos(deg_to_rad(fix_ang(angle - data->player.angle)));
	height = (((float)WIDTH / FOV * 27.0) / p);
	if (height > HEIGHT)
		height = HEIGHT;
	offset = ((float)HEIGHT / 2) - (height / 2);
	//printf("ray ax %f \t ay %f \t bx %f \t by %f \n", ray->ax, ray->ay, ray->bx, ray->by);
	if (fmod(ray->bx, 1) != 0)
		hor_hitp = fmod(ray->bx, 1) * t->width;
	else if (fmod(ray->by, 1) != 0)
		hor_hitp = fmod(ray->by, 1) * t->width;
	//printf("hor_hitp: %d\n", hor_hitp);
	color = find_color(ray->side);\
	i = 0;
	while (i < height)
	{
		ver_hitp = (i / height) * t->height;
		int r = t->pixels[(ver_hitp * t->width + hor_hitp) * t->bytes_per_pixel];
		int g = t->pixels[((ver_hitp) * t->width + hor_hitp) * t->bytes_per_pixel + 1];
		int b = t->pixels[((ver_hitp) * t->width + hor_hitp) * t->bytes_per_pixel + 2];
		color = make_color(r, g, b);
		//color = t->pixels[(ver_hitp * t->width + hor_hitp) * t->bytes_per_pixel];
		putpixel(data->world, ray->no, offset + i, color);
		i++;
	}
}

//temp = mlx_texture_area_to_image(data->mlx, data->walls[side].texture, 
//(uint32_t[2]){horizontal_wall_place, vertical_wall_place}, (uint32_t[2]){1, 1}); //