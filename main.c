#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "include/cub.h"
#include "line.h"
#define FOV 70

typedef struct s_testdata
{
	mlx_t		*mlx;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*grid;
	mlx_image_t	*floor;
	t_line		line;
	bool		display_rays;
}	t_testdata;

#define mapX  8      //map width
#define mapY  8      //map height
#define mapS 64      //map cube size
int map[]=           //the map array. Edit to change level but keep the outer walls
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

float pdx,pdy,pa;

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

void drawRays2D(t_testdata *data)
{
	int r,mx,my,mp,dof; float vx,vy,rx,ry,ra,xo,yo,disV,disH;

	// int rays_per_degree = 10;

	ra = FixAng(pa + FOV / 2);              //ray set back 30 degrees

	r = 0;
	while (r < FOV)
	{
		//---Vertical---
		dof = 0;
		disV = 100000;
		float Tan = tan(degToRad(ra));
		if (cos(degToRad(ra)) > 0.001) //looking left
		{
			rx = (((data->player->instances->x + 4) >> 6) << 6) + 64;
			ry = ((float)(data->player->instances->x + 4) - rx) * Tan + (float)(data->player->instances->y + 4);
			xo = 64;
			yo = -xo * Tan;
		}
		else if (cos(degToRad(ra)) < -0.001) //looking right
		{
			rx = (((data->player->instances->x + 4) >> 6) << 6) - 0.0001;
			ry = ((float)(data->player->instances->x + 4) - rx) * Tan + (float)(data->player->instances->y + 4);
			xo = -64;
			yo = -xo * Tan;
		}
		else							//looking up or down. no hit
		{
			rx = (float)(data->player->instances->x + 4);
			ry = (float)(data->player->instances->y + 4);
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)		//hit
			{
				dof = 8;
				disV = cos(degToRad(ra)) * (rx - (float)(data->player->instances->x + 4)) - sin(degToRad(ra)) * (ry - (float)(data->player->instances->y + 4));
			}
			else                         //check next horizontal
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		vx = rx;
		vy = ry;

		//---Horizontal---
		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		if (sin(degToRad(ra)) > 0.001)		//looking up
		{
			ry = (((data->player->instances->y + 4) / 64) * 64) - 0.0001;
			rx = ((float)(data->player->instances->y + 4) - ry) * Tan + (float)(data->player->instances->x + 4);
			yo = -64;
			xo = -yo * Tan;
		}
		else if (sin(degToRad(ra)) < -0.001)	//looking down
		{
			ry = (((data->player->instances->y + 4) / 64) * 64) + 64;
			rx = ((float)(data->player->instances->y + 4) - ry) * Tan + (float)(data->player->instances->x + 4);
			yo = 64;
			xo = -yo * Tan;
		}
		else								//looking straight left or right
		{
			rx = (float)(data->player->instances->x + 4);
			ry = (float)(data->player->instances->y + 4);
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)		//hit
			{
				dof = 8;
				disH = cos(degToRad(ra)) * (rx - (float)(data->player->instances->x + 4)) - sin(degToRad(ra)) * (ry - (float)(data->player->instances->y + 4));
			}
			else				 //check next horizontal
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		if (disV < disH)			 //horizontal hit first
		{
			rx = vx;
			ry = vy;
			disH = disV;
		}

		int ca = FixAng(pa - ra);
		disH = disH * cos(degToRad(ca));                            //fix fisheye

		int lineH = (mapS * 320) / (disH);
		if (lineH > 320)
			lineH = 320;                     //line height and limit

		int lineOff = 160 - (lineH >> 1);                               //line offset

		int	i = -4;
		while (i < 4)
		{
			data->line = set_line_coords(r * 8 + 530 - i, lineOff, r * 8 + 530 - i, lineOff + lineH);
			ft_line(data->grid, &data->line, 0xFFFFFFFF);
			i++;
		}

		if (data->display_rays)
		{
			data->line = set_line_coords(data->player->instances->x + 4, data->player->instances->y + 4, rx, ry);
			ft_line(data->grid, &data->line, 0xEEEE99FF);
		}
		ra = FixAng(ra - 1);                                                              //go to next ray
		r++;
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
	t_testdata	*data;
	mlx_t		*mlx;

	int ppddxx = pdx * 5;
	int ppddyy = pdy * 5;

	data = param;
	mlx = data->mlx;
	ft_fill(data->grid, data->mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		data->player->instances->x += ppddxx;
		data->player->instances->y += ppddyy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		data->player->instances->x -= ppddxx;
		data->player->instances->y -= ppddyy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		pa+=5;
		pa=FixAng(pa);
		pdx=cos(degToRad(pa));
		pdy=-sin(degToRad(pa));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		pa-=5;
		pa=FixAng(pa);
		pdx=cos(degToRad(pa));
		pdy=-sin(degToRad(pa));
	}
	data->line = set_line_coords(data->player->instances->x + 4, data->player->instances->y + 4, data->player->instances->x + 4 + pdx * 30, data->player->instances->y + 4 + pdy * 30);
	ft_line(data->grid, &data->line, 0xEEEE99FF);
	drawRays2D(data);
}


void input_hook(mlx_key_data_t keydata, void* param)
{
	t_testdata	*data;
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


void drawMap2D(t_testdata *data)
{
	int x,y,xo,yo;
	mlx_image_t	*img;
	for(y=0;y<mapY;y++)
	{
		for(x=0;x<mapX;x++)
		{
			if(map[y*mapX+x]==1){ img = data->wall;} else{ img = data->floor;}
			xo=x*mapS; yo=y*mapS;
			mlx_image_to_window(data->mlx, img, xo, yo);
		}
	}
}

void	draw_player(t_testdata *data)
{
	data->player = mlx_new_image(data->mlx, 8, 8);
	memset(data->player->pixels, 200, data->player->width * data->player->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->player, 284, 348);
}

void	init_textures(t_testdata *data)
{
	data->floor = mlx_new_image(data->mlx, mapS - 1, mapS - 1);
	memset(data->floor->pixels, 100, data->floor->width * data->floor->height * sizeof(int));
	data->wall = mlx_new_image(data->mlx, mapS - 1, mapS - 1);
	memset(data->wall->pixels, 255, data->wall->width * data->wall->height * sizeof(int));
	data->grid = mlx_new_image(data->mlx, 1200, 512);
}

void init()
{
	pa = 0;
	pdx = cos(degToRad(pa));
	pdy = -sin(degToRad(pa));
}

int32_t	main(void)
{
	t_testdata	data;

	if (!(data.mlx = mlx_init(1200, 512, "MLX42", true)))
		return(EXIT_FAILURE);

	init();
	data.display_rays = false;
	init_textures(&data);
	drawMap2D(&data);
	mlx_image_to_window(data.mlx, data.grid, 0, 0);
	draw_player(&data);

	mlx_key_hook(data.mlx, &input_hook, &data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
