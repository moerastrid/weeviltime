#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "./MLX42/include/MLX42/MLX42.h"
#include "cub_include/cub.h"

void	draw_rays_2d(t_data *data, t_rays *rays, mlx_instance_t *player, t_raymath *r_math)
{
	// int rays_per_degree = 10;

	r_math->ra = fix_ang(rays->pa + FOV / 2);              //ray set back 30 degrees

	r_math->r = 0;
	while (r_math->r < FOV)
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
			r_math->mx = (int)(r_math->rx) / MMS;
			r_math->my = (int)(r_math->ry) / MMS;
			r_math->mp = r_math->my * data->max.x + r_math->mx;
			if (r_math->mp > 0 && r_math->mp < data->max.x * data->max.y && data->map[r_math->mp] == 1)		//hit
			{
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
			r_math->rx = r_math->vx;
			r_math->ry = r_math->vy;
			r_math->dish = r_math->disv;
		}

		int ca = fix_ang(rays->pa - r_math->ra);
		r_math->dish = r_math->dish * cos(deg_to_rad(ca));                            //fix fisheye

		int lineH = (MMS * 320) / (r_math->dish);
		if (lineH > 320)
			lineH = 320;                     //line height and limit

		int lineOff = 160 - (lineH >> 1);                               //line offset

		int	i = -4;
		while (i < 4)
		{
			rays->line = set_line_coords(r_math->r * 8 + 1000 - i, lineOff, r_math->r * 8 + 1000 - i, lineOff + lineH);
			ft_line(rays->grid, &rays->line, 0xFFFFFFFF);
			// int a = (float)lineH / 320 * 255;
			// ft_line(rays->grid, &rays->line, 0xFFFFFF00 | a);
			i++;
		}

		if (rays->display_rays)
		{
			rays->line = set_line_coords(player->x + (MMS / 8), player->y + (MMS / 8), r_math->rx, r_math->ry);
			ft_line(rays->grid, &rays->line, 0xEEEE99FF);
		}
		r_math->ra = fix_ang(r_math->ra - 1);                                                              //go to next ray
		r_math->r++;
	}
}

void	ft_fill(t_img *img, mlx_t *mlx)
{
	int	i;
	int	j;

	j = 0;
	while (j < mlx->height)
	{
		i = 0;
		while (i < mlx->width)
		{
			putpixel(img, i, j, 0);
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
	//ft_fill(rays->grid, mlx);
	display_background(rays->grid, data);

	//	draws line to indicate player camera direction
	rays->line = set_line_coords(player->x + (MMS / 8), player->y + (MMS / 8), player->x + (MMS / 8) + rays->pdx * 30, player->y + (MMS / 8) + rays->pdy * 30);
	ft_line(rays->grid, &rays->line, 0xEEEE99FF);
	draw_rays_2d(data, rays, player, &rays->r_math);
}

void drawMap2D(t_data *data)
{
	int x,y,xo,yo;
	mlx_image_t	*img;
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
