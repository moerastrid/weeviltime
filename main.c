#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "include/cub.h"
#include "line.h"
#define FOV 70

typedef struct s_raymath
{
	int r;
	int	mx;
	int	my;
	int	mp;
	int	dof;
	float vx;
	float vy;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	float disV;
	float disH;
}	t_raymath;

typedef struct s_raydata
{
	mlx_t		*mlx;
	t_raymath	r_math;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*grid;
	mlx_image_t	*floor;
	t_line		line;
	bool		display_rays;
	float		pdx;
	float		pdy;
	float		pa;
}	t_raydata;

#define mapX  8      //map width		//moeten in de struct en gebaseerd op de grootte van de gegeven map
#define mapY  8      //map height		//
#define mapS 64      //map cube size
int map[] =           //the map array. Edit to change level but keep the outer walls
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
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

void drawRays2D(t_raydata *raydata, mlx_instance_t *player, t_raymath *r_math)
{
	// int rays_per_degree = 10;

	r_math->ra = FixAng(raydata->pa + FOV / 2);              //ray set back 30 degrees

	r_math->r = 0;
	while (r_math->r < FOV)
	{
		//---Vertical---
		r_math->dof = 0;
		r_math->disV = 100000;
		float Tan = tan(degToRad(r_math->ra));
		if (cos(degToRad(r_math->ra)) > 0.001) //looking left
		{
			r_math->rx = (((player->x + 4) >> 6) << 6) + 64;
			r_math->ry = ((float)(player->x + 4) - r_math->rx) * Tan + (float)(player->y + 4);
			r_math->xo = 64;
			r_math->yo = -r_math->xo * Tan;
		}
		else if (cos(degToRad(r_math->ra)) < -0.001) //looking right
		{
			r_math->rx = (((player->x + 4) >> 6) << 6) - 0.0001;
			r_math->ry = ((float)(player->x + 4) - r_math->rx) * Tan + (float)(player->y + 4);
			r_math->xo = -64;
			r_math->yo = -r_math->xo * Tan;
		}
		else							//looking up or down. no hit
		{
			r_math->rx = (float)(player->x + 4);
			r_math->ry = (float)(player->y + 4);
			r_math->dof = 8;
		}

		while (r_math->dof < 8)
		{
			r_math->mx = (int)(r_math->rx) >> 6;
			r_math->my = (int)(r_math->ry) >> 6;
			r_math->mp = r_math->my * mapX + r_math->mx;
			if (r_math->mp > 0 && r_math->mp < mapX * mapY && map[r_math->mp] == 1)		//hit
			{
				r_math->dof = 8;
				r_math->disV = cos(degToRad(r_math->ra)) * (r_math->rx - (float)(player->x + 4)) - sin(degToRad(r_math->ra)) * (r_math->ry - (float)(player->y + 4));
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
		r_math->disH = 100000;
		Tan = 1.0 / Tan;
		if (sin(degToRad(r_math->ra)) > 0.001)		//looking up
		{
			r_math->ry = (((player->y + 4) / 64) * 64) - 0.0001;
			r_math->rx = ((float)(player->y + 4) - r_math->ry) * Tan + (float)(player->x + 4);
			r_math->yo = -64;
			r_math->xo = -r_math->yo * Tan;
		}
		else if (sin(degToRad(r_math->ra)) < -0.001)	//looking down
		{
			r_math->ry = (((player->y + 4) / 64) * 64) + 64;
			r_math->rx = ((float)(player->y + 4) - r_math->ry) * Tan + (float)(player->x + 4);
			r_math->yo = 64;
			r_math->xo = -r_math->yo * Tan;
		}
		else								//looking straight left or right
		{
			r_math->rx = (float)(player->x + 4);
			r_math->ry = (float)(player->y + 4);
			r_math->dof = 8;
		}

		while (r_math->dof < 8)
		{
			r_math->mx = (int)(r_math->rx) >> 6;
			r_math->my = (int)(r_math->ry) >> 6;
			r_math->mp = r_math->my * mapX + r_math->mx;
			if (r_math->mp > 0 && r_math->mp < mapX * mapY && map[r_math->mp] == 1)		//hit
			{
				r_math->dof = 8;
				r_math->disH = cos(degToRad(r_math->ra)) * (r_math->rx - (float)(player->x + 4)) - sin(degToRad(r_math->ra)) * (r_math->ry - (float)(player->y + 4));
			}
			else				 //check next horizontal
			{
				r_math->rx += r_math->xo;
				r_math->ry += r_math->yo;
				r_math->dof += 1;
			}
		}

		if (r_math->disV < r_math->disH)			 //horizontal hit first
		{
			r_math->rx = r_math->vx;
			r_math->ry = r_math->vy;
			r_math->disH = r_math->disV;
		}

		int ca = FixAng(raydata->pa - r_math->ra);
		r_math->disH = r_math->disH * cos(degToRad(ca));                            //fix fisheye

		int lineH = (mapS * 320) / (r_math->disH);
		if (lineH > 320)
			lineH = 320;                     //line height and limit

		int lineOff = 160 - (lineH >> 1);                               //line offset

		int	i = -4;
		while (i < 4)
		{
			raydata->line = set_line_coords(r_math->r * 8 + 530 - i, lineOff, r_math->r * 8 + 530 - i, lineOff + lineH);
			ft_line(raydata->grid, &raydata->line, 0xFFFFFFFF);
			i++;
		}

		if (raydata->display_rays)
		{
			raydata->line = set_line_coords(player->x + 4, player->y + 4, r_math->rx, r_math->ry);
			ft_line(raydata->grid, &raydata->line, 0xEEEE99FF);
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
	t_raydata		*raydata;
	mlx_t			*mlx;
	mlx_instance_t	*player;

	int ppddxx;
	int ppddyy;

	raydata = param;
	ppddxx = raydata->pdx * 5;
	ppddyy = raydata->pdy * 5;
	mlx = raydata->mlx;
	player = raydata->player->instances;
	ft_fill(raydata->grid, raydata->mlx);
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
		raydata->pa += 5;
		raydata->pa = FixAng(raydata->pa);
		raydata->pdx = cos(degToRad(raydata->pa));
		raydata->pdy = -sin(degToRad(raydata->pa));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		raydata->pa -= 5;
		raydata->pa = FixAng(raydata->pa);
		raydata->pdx = cos(degToRad(raydata->pa));
		raydata->pdy = -sin(degToRad(raydata->pa));
	}
	raydata->line = set_line_coords(player->x + 4, player->y + 4, player->x + 4 + raydata->pdx * 30, player->y + 4 + raydata->pdy * 30);
	ft_line(raydata->grid, &raydata->line, 0xEEEE99FF);
	drawRays2D(raydata, player, &raydata->r_math);
}

void input_hook(mlx_key_data_t keydata, void* param)
{
	t_raydata	*data;
	mlx_t		*mlx;

	data = param;
	mlx = data->mlx;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_R)
	{
		if (data->display_rays == false)
			data->display_rays = true;
		else
			data->display_rays = false;
	}
}


void drawMap2D(t_raydata *raydata)
{
	int x,y,xo,yo;
	mlx_image_t	*img;
	y = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			if (map[y * mapX + x] == 1)
				img = raydata->wall;
			else
				img = raydata->floor;
			xo = x * mapS;
			yo = y * mapS;
			mlx_image_to_window(raydata->mlx, img, xo, yo);
			x++;
		}
		y++;
	}
}

void	draw_player(t_raydata *data)
{
	data->player = mlx_new_image(data->mlx, 8, 8);
	memset(data->player->pixels, 200, data->player->width * data->player->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->player, 284, 348);
}

void	init_textures(t_raydata *data)
{
	data->floor = mlx_new_image(data->mlx, mapS - 1, mapS - 1);
	memset(data->floor->pixels, 100, data->floor->width * data->floor->height * sizeof(int));
	data->wall = mlx_new_image(data->mlx, mapS - 1, mapS - 1);
	memset(data->wall->pixels, 255, data->wall->width * data->wall->height * sizeof(int));
	data->grid = mlx_new_image(data->mlx, 1200, 512);
}

void init(t_raydata *raydata)
{
	raydata->pa = 0;
	raydata->pdx = cos(degToRad(raydata->pa));
	raydata->pdy = -sin(degToRad(raydata->pa));
}

int32_t	main(void)
{
	t_raydata	raydata;

	ft_bzero(&raydata, sizeof(t_raydata));
	if (!(raydata.mlx = mlx_init(1200, 512, "MLX42", true)))
		return(EXIT_FAILURE);

	init(&raydata);
	raydata.display_rays = false;
	init_textures(&raydata);
	drawMap2D(&raydata);
	mlx_image_to_window(raydata.mlx, raydata.grid, 0, 0);
	draw_player(&raydata);

	mlx_key_hook(raydata.mlx, &input_hook, &raydata);
	mlx_loop_hook(raydata.mlx, &hook, &raydata);
	mlx_loop(raydata.mlx);

	mlx_terminate(raydata.mlx);
	return (EXIT_SUCCESS);
}
