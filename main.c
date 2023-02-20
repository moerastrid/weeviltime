#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "include/cub.h"

typedef mlx_image_t	t_img;

typedef struct s_map
{
	t_img	*img;
	mlx_t	*mlx;
	char	*path;
	int		hor;
	int		ver;
	int		xa;
	int		xb;
	int		ya;
	int		yb;
	int		offsetx;
	int		offsety;
	int		zoom;
	int		steepness;
	float	angle;
}	t_map;

void	ft_pixelputwrap(t_img *img, const uint32_t x, const uint32_t y, unsigned int color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

void	updownleftright(t_img *img, t_map *mapdata, float mn[2])
{
	while (mapdata->ya <= mapdata->yb && mapdata->xa <= mapdata->xb)
	{
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEEEEEEFF);
		if (mapdata->ya <= (mn[0] * mapdata->xa) + mn[1]
			&& (mapdata->ya + 1) >= (mn[0] * mapdata->xa) + mn[1])
			mapdata->xa++;
		else
			mapdata->ya++;
	}
	return ;
}

void	downupleftright(t_img *img, t_map *mapdata, float mn[2])
{
	while (mapdata->ya >= mapdata->yb && mapdata->xa <= mapdata->xb)
	{
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0x99EEEEFF);
		if (mapdata->ya <= (mn[0] * mapdata->xa) + mn[1]
			&& (mapdata->ya + 1) > (mn[0] * mapdata->xa + mn[1]))
			mapdata->xa++;
		else
			mapdata->ya--;
	}
}

void	updownrightleft(t_img *img, t_map *mapdata, float mn[2])
{
	while (mapdata->ya <= mapdata->yb && mapdata->xa >= mapdata->xb)
	{
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEE99EEFF);
		if (mapdata->ya >= (mn[0] * mapdata->xa) + mn[1]
			&& (mapdata->ya - 1) <= (mn[0] * mapdata->xa) + mn[1])
			mapdata->xa--;
		else
			mapdata->ya++;
	}
}

void	downuprightleft(t_img *img, t_map *mapdata, float mn[2])
{
	while (mapdata->ya >= mapdata->yb && mapdata->xa >= mapdata->xb)
	{
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEEEE99FF);
		if (mapdata->ya >= (mn[0] * mapdata->xa) + mn[1]
			&& (mapdata->ya - 1) <= (mn[0] * mapdata->xa + mn[1]))
			mapdata->xa--;
		else
			mapdata->ya--;
	}
}

void	ft_line(t_img *img, t_map *mapdata)
{
	float		xd;
	float		yd;
	float		mn[2];

	xd = mapdata->xb - mapdata->xa;
	yd = mapdata->yb - mapdata->ya;
	mn[0] = yd / xd;
	mn[1] = mapdata->ya - (mapdata->xa * mn[0]);
	if (mapdata->ya <= mapdata->yb && mapdata->xa <= mapdata->xb)
		updownleftright(img, mapdata, mn);
	else if (mapdata->ya >= mapdata->yb && mapdata->xa <= mapdata->xb)
		downupleftright(img, mapdata, mn);
	else if (mapdata->ya <= mapdata->yb && mapdata->xa >= mapdata->xb)
		updownrightleft(img, mapdata, mn);
	else if (mapdata->ya >= mapdata->yb && mapdata->xa >= mapdata->xb)
		downuprightleft(img, mapdata, mn);
	return ;
}

typedef struct s_testdata
{
	mlx_t		*mlx;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*grid;
	mlx_image_t	*floor;
	t_map		map;
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

float px,py,pdx,pdy,pa;

float degToRad(int a)
{
	return (a * M_PI / 180.0);
}

int FixAng(int a)
{ 
	if(a > 359)
		a -= 360;
	if(a < 0)
		a += 360;
	return (a);
}

void drawline(t_testdata *data, int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
 
	dx=x1-x0;
	dy=y1-y0;
	
	x=x0;
	y=y0;
	
	p=2*dy-dx;
	
	while(x<x1)
	{
		if(p>=0)
		{
			mlx_put_pixel(data->grid, x,y,255);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			mlx_put_pixel(data->grid, x,y,255);
			p=p+2*dy;
		}
		x=x+1;
	}
}

void hook(void* param)
{
	t_testdata	*data;
	mlx_t		*mlx;

	data = param;
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		data->player->instances->x += pdx*5;
		data->player->instances->y += pdy*5;
		// drawline(data, data->player->instances->x, data->player->instances->y, 500, 255);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		data->player->instances->y -= pdy*5;
		data->player->instances->x -= pdx*5;
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
	// data->map.xa = data->player->instances->x;
	// data->map.xb = data->player->instances->y;
	// data->map.ya = data->player->instances->x + pdx * 50;
	// data->map.yb = data->player->instances->y + pdy * 50;
	// ft_line(data->grid, &data->map);
	// drawline(data, 300, 500, 250, 300);
	// drawline(data, data->player->instances->x, data->player->instances->y, data->player->instances->x + pdx * 50, data->player->instances->y + pdy * 50);
	
}

/*
void input_hook(mlx_key_data_t keydata, void* param)
{
	t_testdata	*data;
	mlx_t		*mlx;

	data = param;
	mlx = data->mlx;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
	{
		data->player->instances->x += pdx*5;
		data->player->instances->y += pdy*5;
		// drawline(data, data->player->instances->x, data->player->instances->y, 500, 255);
	}
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
	{
		data->player->instances->y -= pdy*5;
		data->player->instances->x -= pdx*5;
	}
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
	{
		pa+=5;
		pa=FixAng(pa);
		pdx=cos(degToRad(pa));
		pdy=-sin(degToRad(pa));
	}
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
	{
		pa-=5;
		pa=FixAng(pa);
		pdx=cos(degToRad(pa));
		pdy=-sin(degToRad(pa));
	}
}
*/

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
	memset(data->player->pixels, 255, data->player->width * data->player->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->player, 284, 348);
}

void	init_textures(t_testdata *data)
{
	data->floor = mlx_new_image(data->mlx, mapS - 1, mapS - 1);
	memset(data->floor->pixels, 100, data->floor->width * data->floor->height * sizeof(int));
	data->wall = mlx_new_image(data->mlx, mapS - 1, mapS - 1);
	memset(data->wall->pixels, 255, data->wall->width * data->wall->height * sizeof(int));
	data->grid = mlx_new_image(data->mlx, 1024, 512);
}

void init()
{
 px=150; py=400; pa=90;
 pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa)); 
}

// void	hook(void *param)
// {
// 	t_testdata	*data;
// 	mlx_t		*mlx;

// 	data = param;
// 	mlx = data->mlx;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	drawline(data, data->player->instances->x, data->player->instances->y, data->player->instances->x + pdx * 5, data->player->instances->y + pdy * 5);
// }

int32_t	main(void)
{
	t_testdata	data;

	data.map.xa = 300;
	data.map.xb = 200;
	data.map.ya = 500;
	data.map.yb = 400;
	if (!(data.mlx = mlx_init(1024, 512, "MLX42", true)))
		return(EXIT_FAILURE);

	init();
	init_textures(&data);
	drawMap2D(&data);
	mlx_image_to_window(data.mlx, data.grid, 0, 0);
	draw_player(&data);

	// mlx_key_hook(data.mlx, &input_hook, &data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
