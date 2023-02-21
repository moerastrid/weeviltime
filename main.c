#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "include/cub.h"
#define FOV 90

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
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEEEE99FF);
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
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEEEE99FF);
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
		ft_pixelputwrap(img, mapdata->xa, mapdata->ya, 0xEEEE99FF);
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
	int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 

	// int rays_per_degree = 10;
	
	ra=FixAng(pa+FOV/2);                                                              //ray set back 30 degrees
	
	for(r=0;r<FOV;r++)
	{
		//---Vertical--- 
		dof=0; side=0; disV=100000;
		float Tan=tan(degToRad(ra));
		if(cos(degToRad(ra)) > 0.001) //looking left
		{
			rx=(((data->player->instances->x + 4)>>6)<<6)+64;
			ry=((float)(data->player->instances->x + 4)-rx)*Tan+(float)(data->player->instances->y + 4);
			xo= 64; yo=-xo*Tan;
		}
		else if(cos(degToRad(ra)) < -0.001) //looking right
		{
			rx=(((data->player->instances->x + 4)>>6)<<6) -0.0001;
			ry=((float)(data->player->instances->x + 4)-rx)*Tan+(float)(data->player->instances->y + 4);
			xo=-64; yo=-xo*Tan;
		}
		else { //looking up or down. no hit
			rx=(float)(data->player->instances->x + 4);
			ry=(float)(data->player->instances->y + 4);
			dof=8;
		}                                                    

		while(dof<8) 
		{ 
			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
			if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-(float)(data->player->instances->x + 4))-sin(degToRad(ra))*(ry-(float)(data->player->instances->y + 4));}//hit         
			else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
		} 
		vx=rx; vy=ry;

		//---Horizontal---
		dof=0; disH=100000;
		Tan=1.0/Tan; 
		if(sin(degToRad(ra))> 0.001){ ry=(((data->player->instances->y + 4)>>6)<<6) -0.0001; rx=((float)(data->player->instances->y + 4)-ry)*Tan+(float)(data->player->instances->x + 4); yo=-64; xo=-yo*Tan;}//looking up 
		else if(sin(degToRad(ra))<-0.001){ ry=(((data->player->instances->y + 4)>>6)<<6)+64;      rx=((float)(data->player->instances->y + 4)-ry)*Tan+(float)(data->player->instances->x + 4); yo= 64; xo=-yo*Tan;}//looking down
		else{
			rx=(float)(data->player->instances->x + 4); ry=(float)(data->player->instances->y + 4); dof=8;
		}                                                   //looking straight left or right
	
		while(dof<8) 
		{ 
			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
			if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-(float)(data->player->instances->x + 4))-sin(degToRad(ra))*(ry-(float)(data->player->instances->y + 4));}//hit
			else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
		}
		

//   glColor3f(0,0.8,0);
		if(disV<disH){ rx=vx; ry=vy; disH=disV; /*glColor3f(0,0.6,0);*/}                  //horizontal hit first
//   glLineWidth(2); glBegin(GL_LINES); glVertex2i((float)data->player->instances->x,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
				
		int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
		int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
		int lineOff = 160 - (lineH>>1);                                               //line offset
		data->map.xa = r*8+530;
		data->map.ya = lineOff;
		data->map.xb = r*8+530;
		data->map.yb = lineOff+lineH;
		ft_line(data->grid, &data->map);
		// glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  
		data->map.xa = data->player->instances->x + 4;
		data->map.ya = data->player->instances->y + 4;
		data->map.xb = rx;
		data->map.yb = ry;
		ft_line(data->grid, &data->map);
		ra=FixAng(ra-1);                                                              //go to next ray
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
		// data->player->instances->x += pdx*5;
		// data->player->instances->y += pdy*5;
		// drawline(data, data->player->instances->x, data->player->instances->y, 500, 255);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		data->player->instances->x -= ppddxx;
		data->player->instances->y -= ppddyy;
		// data->player->instances->x -= pdx*5;
		// data->player->instances->y -= pdy*5;
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
	// test_image->instances->x = data->player->instances->x + ppddxx * 4;
	// test_image->instances->y = data->player->instances->y + ppddyy * 4;
	// test_image2->instances->x = data->player->instances->x - ppddxx * 4;
	// test_image2->instances->y = data->player->instances->y - ppddyy * 4;
	data->map.xa = data->player->instances->x + 4;
	data->map.ya = data->player->instances->y + 4;
	data->map.xb = data->player->instances->x + 4 + pdx * 30;
	data->map.yb = data->player->instances->y + 4 + pdy * 30;
	ft_line(data->grid, &data->map);
	drawRays2D(data);
	// mlx_close_window(mlx);
	// drawline(data, 200, 100, 250, 250);
	// drawline(data, 250, 200, 200, 250);
	// betterLineDraw(data, data->player->instances->x, data->player->instances->y, data->player->instances->x + ppddxx * 10, data->player->instances->y + ppddyy * 10);
	
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
	memset(data->player->pixels, 200, data->player->width * data->player->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->player, 284, 348);
	// test_image = mlx_new_image(data->mlx, 8, 8);
	// memset(test_image->pixels, 150, test_image->width * test_image->height * sizeof(int));
	// mlx_image_to_window(data->mlx, test_image, 284, 348);
	// test_image2 = mlx_new_image(data->mlx, 8, 8);
	// memset(test_image2->pixels, 150, test_image2->width * test_image2->height * sizeof(int));
	// mlx_image_to_window(data->mlx, test_image2, 284, 348);
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
	px=150; py=400; pa=0;
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
