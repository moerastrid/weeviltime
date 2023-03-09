/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   old_raycasting.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 14:08:55 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/06 15:34:46 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/MLX42.h"
#include "cub_include/cub.h"


//static void	move_hook(void *param)
//{
//	t_data			*data;
//	t_rays			*rays;
//	mlx_t			*mlx;
//	mlx_instance_t	*player;
//	t_collision		*coll;

//	data = param;
//	rays = &data->rays;
//	player = rays->player->instances;
//	rays->ppddxx = rays->pdx * (MMS / 8);
//	rays->ppddyy = rays->pdy * (MMS / 8);
//	mlx = data->mlx;
//	coll = &data->coll;
//	get_collision(data, rays, coll);
//	if (mlx_is_key_down(mlx, MLX_KEY_UP))
//	{
//		if (data->map[coll->ipy * data->max.x + coll->ipx_add_xo] == 0)
//			data->player.pos_x += rays->ppddxx;
//		if (data->map[coll->ipy_add_yo * data->max.x + coll->ipx] == 0)
//			data->player.pos_y += rays->ppddyy;
//		player->x = (int)data->player.pos_x;
//		player->y = (int)data->player.pos_y;
//	}
//	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
//	{
//		if (data->map[coll->ipy * data->max.x + coll->ipx_sub_xo] == 0)
//			data->player.pos_x -= rays->ppddxx;
//		if (data->map[coll->ipy_sub_yo * data->max.x + coll->ipx] == 0)
//			data->player.pos_y -= rays->ppddyy;
//		player->x = (int)data->player.pos_x;
//		player->y = (int)data->player.pos_y;
//	}
//}

//static void	turn_hook(void *param)
//{
//	t_data	*data;
//	t_rays	*rays;

//	data = param;
//	rays = &data->rays;
//	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
//	{
//		rays->pa += 5;
//		rays->pa = fix_ang(rays->pa);
//		rays->pdx = cos(deg_to_rad(rays->pa));
//		rays->pdy = -sin(deg_to_rad(rays->pa));
//	}
//	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
//	{
//		rays->pa -= 5;
//		rays->pa = fix_ang(rays->pa);
//		rays->pdx = cos(deg_to_rad(rays->pa));
//		rays->pdy = -sin(deg_to_rad(rays->pa));
//	}
//}

//static void	get_collision(t_data *data, t_rays *rays, t_collision *coll)
//{
//	//	x offset to check map
//	if (rays->pdx < 0)
//		coll->xo = -(MMS / 3);
//	else
//		coll->xo = (MMS / 3);
//	//	y offset to check map
//	if (rays->pdy < 0)
//		coll->yo = -(MMS / 3);
//	else
//		coll->yo = (MMS / 3);
//	//	x position and offset
//	coll->ipx = (data->player.pos_x + (MMS / 8)) / MMS;
//	coll->ipx_add_xo = ((data->player.pos_x + (MMS / 8)) + coll->xo) / MMS;
//	coll->ipx_sub_xo = ((data->player.pos_x + (MMS / 8)) - coll->xo) / MMS;
//	//	y position and offset
//	coll->ipy = (data->player.pos_y + (MMS / 8)) / MMS;
//	coll->ipy_add_yo = ((data->player.pos_y + (MMS / 8)) + coll->yo) / MMS;
//	coll->ipy_sub_yo = ((data->player.pos_y + (MMS / 8)) - coll->yo) / MMS;
//}

void	draw_rays_2d(t_data *data, t_rays *rays, mlx_instance_t *player, t_raymath *r_math)
{
	float rays_per_degree = 10;
	static uint32_t color = 0x770000FF;
	color = 0x770000FF;

	r_math->ra = fix_ang(rays->pa + FOV / 2);              //ray set back 30 degrees

	r_math->r = 0;
	while (r_math->r < FOV * rays_per_degree)
	{
		//---Vertical---
		r_math->dof = 0;
		r_math->disv = 100000;
		float Tan = tan(deg_to_rad(r_math->ra));
		if (cos(deg_to_rad(r_math->ra)) > 0.001) //looking left
		{
			r_math->rx = (((player->x + (MMS / 8)) / MMS) * MMS) + MMS;
			r_math->ry = ((float)(player->x + (MMS / 8)) - r_math->rx) * Tan + (float)(player->y + (MMS / 8));
			r_math->xo = MMS;
			r_math->yo = -r_math->xo * Tan;
		}
		else if (cos(deg_to_rad(r_math->ra)) < -0.001) //looking right
		{
			r_math->rx = (((player->x + (MMS / 8)) / MMS) * MMS) - 0.0001;
			r_math->ry = ((float)(player->x + (MMS / 8)) - r_math->rx) * Tan + (float)(player->y + (MMS / 8));
			r_math->xo = -MMS;
			r_math->yo = -r_math->xo * Tan;
		}
		else							//looking up or down. no hit
		{
			r_math->rx = (float)(player->x + (MMS / 8));
			r_math->ry = (float)(player->y + (MMS / 8));
			r_math->dof = DOF;
		}

		while (r_math->dof < DOF)
		{
			r_math->mx = (int)(r_math->rx) / MMS;
			r_math->my = (int)(r_math->ry) / MMS;
			r_math->mp = r_math->my * data->max.x + r_math->mx;
			if (r_math->mp > 0 && r_math->mp < data->max.x * data->max.y && data->map[r_math->mp] == 1)		//hit
			{
				r_math->dof = DOF;
				r_math->disv = cos(deg_to_rad(r_math->ra)) * (r_math->rx - (float)(player->x + (MMS / 8))) - sin(deg_to_rad(r_math->ra)) * (r_math->ry - (float)(player->y + (MMS / 8)));
			}
			else                         //check next horizontal
			{
				r_math->rx += r_math->xo;
				r_math->ry += r_math->yo;
				r_math->dof += 1;
			}
		}
		r_math->vx = r_math->rx;
		r_math->vy = r_math->ry;

		//---Horizontal---
		r_math->dof = 0;
		r_math->dish = 100000;
		Tan = 1.0 / Tan;
		if (sin(deg_to_rad(r_math->ra)) > 0.001)		//looking up
		{
			r_math->ry = (((player->y + (MMS / 8)) / MMS) * MMS) - 0.0001;
			r_math->rx = ((float)(player->y + (MMS / 8)) - r_math->ry) * Tan + (float)(player->x + (MMS / 8));
			r_math->yo = -MMS;
			r_math->xo = -r_math->yo * Tan;
		}
		else if (sin(deg_to_rad(r_math->ra)) < -0.001)	//looking down
		{
			r_math->ry = (((player->y + (MMS / 8)) / MMS) * MMS) + MMS;
			r_math->rx = ((float)(player->y + (MMS / 8)) - r_math->ry) * Tan + (float)(player->x + (MMS / 8));
			r_math->yo = MMS;
			r_math->xo = -r_math->yo * Tan;
		}
		else								//looking straight left or right
		{
			r_math->rx = (float)(player->x + (MMS / 8));
			r_math->ry = (float)(player->y + (MMS / 8));
			r_math->dof = DOF;
		}

		while (r_math->dof < DOF)
		{
			r_math->mx = r_math->rx / MMS;
			r_math->my = r_math->ry / MMS;
			r_math->mp = r_math->my * data->max.x + r_math->mx;
			if (r_math->mp > 0 && r_math->mp < data->max.x * data->max.y && data->map[r_math->mp] == 1)		//hit
			{
				// printf("foo\n");
				r_math->dof = DOF;
				r_math->dish = cos(deg_to_rad(r_math->ra)) * (r_math->rx - (float)(player->x + (MMS / 8))) - sin(deg_to_rad(r_math->ra)) * (r_math->ry - (float)(player->y + (MMS / 8)));
			}
			else				 //check next horizontal
			{
				r_math->rx += r_math->xo;
				r_math->ry += r_math->yo;
				r_math->dof += 1;
			}
		}

		if (r_math->disv < r_math->dish)			 //horizontal hit first
		{
			// printf("bar\n");
			r_math->rx = r_math->vx;
			r_math->ry = r_math->vy;
			r_math->dish = r_math->disv;
		}

		// float ca = fix_ang(rays->pa - r_math->ra);
		// r_math->dish = r_math->dish * cos(deg_to_rad(ca));                            //fix fisheye


		// int lineH = (MMS * HEIGHT) / (r_math->dish);
		// int lineH = lineH * (WIDTH / FOV / 8); // rescale for correct aspect ratio
		float lineH = (1.0 / r_math->dish) * ((float)WIDTH / FOV * 500); // rescale for correct aspect ratio
		if (lineH > HEIGHT)
			lineH = HEIGHT;                     //line height and limit

		float lineOff = ((float)HEIGHT / 2) - (lineH / 2);                               //line offset
		// printf("%f\n", r_math->dish);
		float bar_width = (float)WIDTH / FOV / rays_per_degree;


		int	i = 0;
		while (i < bar_width)
		{
			rays->line = set_line_coords((float)r_math->r * bar_width + i, lineOff, (float)r_math->r * bar_width + i, lineOff + lineH);
			// ft_line(rays->grid, &rays->line, 0xFFFFFFFF);
			ft_line(rays->grid, &rays->line, color);
			// int a = (float)lineH / 320 * 255;
			// ft_line(rays->grid, &rays->line, 0xFFFFFF00 | a);
			i++;
		}

		if (color == 0x770000FF)
			color = 0x007700FF;
		else if (color == 0x007700FF)
			color = 0x000077FF;
		else if (color == 0x000077FF)
			color = 0x770000FF;

		if (rays->display_rays)
		{
			rays->line = set_line_coords(player->x + (MMS / 8), player->y + (MMS / 8), r_math->rx, r_math->ry);
			ft_line(rays->grid, &rays->line, 0xEEEE99FF);
		}
		r_math->ra = fix_ang(r_math->ra - 1.0f / rays_per_degree);                                                              //go to next ray
		r_math->r++;
	}
}

void	ft_fill(t_img *img, mlx_t *mlx, unsigned int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < mlx->height)
	{
		i = 0;
		while (i < mlx->width)
		{
			putpixel(img, i, j, color);
			i++;
		}
		j++;
	}
}

void hook(void* param)
{
	t_data			*data;
	t_rays			*rays;
	mlx_instance_t	*player;

	data = param;
	rays = &data->rays;
	player = rays->player->instances;
	ft_fill(rays->grid, data->mlx);
	// display_background(rays->grid, data);

	//	draws line to indicate player camera direction
	rays->line = set_line_coords( \
	player->x + (MMS / 8), \
	player->y + (MMS / 8), \
	player->x + (MMS / 8) + rays->pdx * 30, \
	player->y + (MMS / 8) + rays->pdy * 30);
	ft_line(rays->grid, &rays->line, 0xEEEE99FF);
	draw_rays_2d(data, rays, player, &rays->r_math);
}

void drawMap2D(t_data *data)
{
	int x,y,xo,yo;
	t_img	*img;
	y = 0;
	while (y < data->max.y)
	{
		x = 0;
		while (x < data->max.x)
		{
			if (data->map[y * data->max.x + x] == 1)
				img = data->rays.wall;
			else
				img = data->rays.floor;
			xo = x * MMS;
			yo = y * MMS;
			mlx_image_to_window(data->mlx, img, xo, yo);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data)
{
	data->rays.player = mlx_new_image(data->mlx, MMS / 4, MMS / 4);
	memset(data->rays.player->pixels, 200, data->rays.player->width * data->rays.player->height * sizeof(int));
	printf("player x: %d\nplayer y: %d\n", data->player.x, data->player.y);				//weg
	printf("player x: %f\nplayer y: %f\n", data->player.pos_x, data->player.pos_y);		//weg
	mlx_image_to_window(data->mlx, data->rays.player, (data->player.x * MMS) + (MMS / 2) - (MMS / 8), (data->player.y * MMS) + (MMS / 2) - (MMS / 8));
}

void	init_textures(t_data *data)
{
	data->rays.floor = mlx_new_image(data->mlx, MMS - 1, MMS - 1);
	memset(data->rays.floor->pixels, 100, data->rays.floor->width * data->rays.floor->height * sizeof(int));
	data->rays.wall = mlx_new_image(data->mlx, MMS - 1, MMS - 1);
	memset(data->rays.wall->pixels, 255, data->rays.wall->width * data->rays.wall->height * sizeof(int));
	data->rays.grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
}

void	init_raydata(t_data *data, t_rays *rays)
{
	rays->pa = data->player.direction;
	rays->pdx = cos(deg_to_rad(rays->pa));
	rays->pdy = -sin(deg_to_rad(rays->pa));
	rays->display_rays = false;
}
