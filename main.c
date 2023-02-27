#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "include/cub.h"
#include "line.h"
#include "raycaster.h"
#define FOV 70

#define mapX  8      //map width		//moeten in de struct en gebaseerd op de grootte van de gegeven map
#define mapY  8      //map height		//
#define mapS 16      //map cube size
#define DOF 16
int map[] =           //the map array. Edit to change level but keep the outer walls
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

float degToRad(int a)
{
	return (a * M_PI / 180.0);
}

float FixAng(float a)
{
	if(a > 359)
		a -= 360;
	if(a < 0)
		a += 360;
	return (a);
}

void drawRays2D(t_data *data, t_rays *rays, mlx_instance_t *player, t_raymath *r_math)
{
	// int rays_per_degree = 10;

	r_math->ra = FixAng(rays->pa + FOV / 2);              //ray set back 30 degrees

	r_math->r = 0;
	while (r_math->r < FOV)
	{
		//---Vertical---
		r_math->dof = 0;
		r_math->disv = 100000;
		float Tan = tan(degToRad(r_math->ra));
		if (cos(degToRad(r_math->ra)) > 0.001) //looking left
		{
			r_math->rx = (((player->x + 4) / mapS) * mapS) + mapS;
			r_math->ry = ((float)(player->x + 4) - r_math->rx) * Tan + (float)(player->y + 4);
			r_math->xo = mapS;
			r_math->yo = -r_math->xo * Tan;
		}
		else if (cos(degToRad(r_math->ra)) < -0.001) //looking right
		{
			r_math->rx = (((player->x + 4) / mapS) * mapS) - 0.0001;
			r_math->ry = ((float)(player->x + 4) - r_math->rx) * Tan + (float)(player->y + 4);
			r_math->xo = -mapS;
			r_math->yo = -r_math->xo * Tan;
		}
		else							//looking up or down. no hit
		{
			r_math->rx = (float)(player->x + 4);
			r_math->ry = (float)(player->y + 4);
			r_math->dof = DOF;
		}

		while (r_math->dof < DOF)
		{
			r_math->mx = (int)(r_math->rx) / mapS;
			r_math->my = (int)(r_math->ry) / mapS;
			r_math->mp = r_math->my * data->map_x + r_math->mx;
			if (r_math->mp > 0 && r_math->mp < data->map_x * data->map_y && data->final_map[r_math->mp] == 1)		//hit
			{
				r_math->dof = DOF;
				r_math->disv = cos(degToRad(r_math->ra)) * (r_math->rx - (float)(player->x + 4)) - sin(degToRad(r_math->ra)) * (r_math->ry - (float)(player->y + 4));
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
		if (sin(degToRad(r_math->ra)) > 0.001)		//looking up
		{
			r_math->ry = (((player->y + 4) / mapS) * mapS) - 0.0001;
			r_math->rx = ((float)(player->y + 4) - r_math->ry) * Tan + (float)(player->x + 4);
			r_math->yo = -mapS;
			r_math->xo = -r_math->yo * Tan;
		}
		else if (sin(degToRad(r_math->ra)) < -0.001)	//looking down
		{
			r_math->ry = (((player->y + 4) / mapS) * mapS) + mapS;
			r_math->rx = ((float)(player->y + 4) - r_math->ry) * Tan + (float)(player->x + 4);
			r_math->yo = mapS;
			r_math->xo = -r_math->yo * Tan;
		}
		else								//looking straight left or right
		{
			r_math->rx = (float)(player->x + 4);
			r_math->ry = (float)(player->y + 4);
			r_math->dof = DOF;
		}

		while (r_math->dof < DOF)
		{
			r_math->mx = (int)(r_math->rx) / mapS;
			r_math->my = (int)(r_math->ry) / mapS;
			r_math->mp = r_math->my * data->map_x + r_math->mx;
			if (r_math->mp > 0 && r_math->mp < data->map_x * data->map_y && data->final_map[r_math->mp] == 1)		//hit
			{
				r_math->dof = DOF;
				r_math->dish = cos(degToRad(r_math->ra)) * (r_math->rx - (float)(player->x + 4)) - sin(degToRad(r_math->ra)) * (r_math->ry - (float)(player->y + 4));
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

		int ca = FixAng(rays->pa - r_math->ra);
		r_math->dish = r_math->dish * cos(degToRad(ca));                            //fix fisheye

		int lineH = (mapS * 320) / (r_math->dish);
		if (lineH > 320)
			lineH = 320;                     //line height and limit

		int lineOff = 160 - (lineH >> 1);                               //line offset

		int	i = -4;
		while (i < 4)
		{
			rays->line = set_line_coords(r_math->r * 8 + 1000 - i, lineOff, r_math->r * 8 + 1000 - i, lineOff + lineH);
			int a = (float)lineH / 320 * 255;
			// ft_line(rays->grid, &rays->line, 0xFFFFFFFF);
			ft_line(rays->grid, &rays->line, 0xFFFFFF00 | a);
			i++;
		}

		if (rays->display_rays)
		{
			rays->line = set_line_coords(player->x + 4, player->y + 4, r_math->rx, r_math->ry);
			ft_line(rays->grid, &rays->line, 0xEEEE99FF);
		}
		r_math->ra = FixAng(r_math->ra - 1);                                                              //go to next ray
		r_math->r++;
	}
}

void	ft_fill(t_img *img, mlx_t *mlx)
{
	int				i;
	int				j;

	j = 0;
	while (j < mlx->height)
	{
		i = 0;
		while (i < mlx->width)
		{
			ft_pixelputwrap(img, i, j, 0);
			i++;
		}
		j++;
	}
}

void hook(void* param)
{
	t_data			*data;
	t_rays			*rays;
	mlx_t			*mlx;
	mlx_instance_t	*player;
	int				ppddxx;
	int 			ppddyy;

	data = param;
	rays = &data->rays;
	ppddxx = rays->pdx * 2;
	ppddyy = rays->pdy * 2;
	mlx = data->mlx;
	player = rays->player->instances;
	ft_fill(rays->grid, mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		player->x += ppddxx;
		player->y += ppddyy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		player->x -= ppddxx;
		player->y -= ppddyy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		rays->pa += 5;
		rays->pa = FixAng(rays->pa);
		rays->pdx = cos(degToRad(rays->pa));
		rays->pdy = -sin(degToRad(rays->pa));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		rays->pa -= 5;
		rays->pa = FixAng(rays->pa);
		rays->pdx = cos(degToRad(rays->pa));
		rays->pdy = -sin(degToRad(rays->pa));
	}
	rays->line = set_line_coords(player->x + 4, player->y + 4, player->x + 4 + rays->pdx * 30, player->y + 4 + rays->pdy * 30);
	ft_line(rays->grid, &rays->line, 0xEEEE99FF);
	drawRays2D(data, rays, player, &rays->r_math);
}

void input_hook(mlx_key_data_t keydata, void* param)
{
	t_data	*data;
	mlx_t	*mlx;

	data = param;
	mlx = data->mlx;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_R)
			data->rays.display_rays = !data->rays.display_rays;
	}
}

void drawMap2D(t_data *data)
{
	int x,y,xo,yo;
	mlx_image_t	*img;
	y = 0;
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->final_map[y * data->map_x + x] == 1)
				img = data->rays.wall;
			else
				img = data->rays.floor;
			xo = x * mapS;
			yo = y * mapS;
			mlx_image_to_window(data->mlx, img, xo, yo);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data)
{
	data->rays.player = mlx_new_image(data->mlx, 8, 8);
	memset(data->rays.player->pixels, 200, data->rays.player->width * data->rays.player->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->rays.player, data->player.x * mapS, data->player.y * mapS);
}

void	init_textures(t_data *data)
{
	data->rays.floor = mlx_new_image(data->mlx, mapS - 1, mapS - 1);
	memset(data->rays.floor->pixels, 100, data->rays.floor->width * data->rays.floor->height * sizeof(int));
	data->rays.wall = mlx_new_image(data->mlx, mapS - 1, mapS - 1);
	memset(data->rays.wall->pixels, 255, data->rays.wall->width * data->rays.wall->height * sizeof(int));
	data->rays.grid = mlx_new_image(data->mlx, WIDTH, HEIGHT);
}

void init(t_rays *rays)
{
	rays->pa = 0;
	rays->pdx = cos(degToRad(rays->pa));
	rays->pdy = -sin(degToRad(rays->pa));
	rays->display_rays = false;
}

void	leakfunc(void)
{
	system("leaks -q cub3D");
}

void	free_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int32_t	main(int argc, char **argv)
{
	t_data	data;

	// atexit(leakfunc);
	ft_bzero(&data, sizeof(t_data));
	if (setup(argc, argv, &data))
		return (EXIT_FAILURE);
	// if (!(rays.mlx = mlx_init(1200, 512, "MLX42", true)))
	// 	return(EXIT_FAILURE);

	init(&data.rays);
	init_textures(&data);
	drawMap2D(&data);
	mlx_image_to_window(data.mlx, data.rays.grid, 0, 0);
	draw_player(&data);

	mlx_key_hook(data.mlx, &input_hook, &data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
