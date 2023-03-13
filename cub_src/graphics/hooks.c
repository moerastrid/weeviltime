/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 22:04:17 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/13 20:55:57 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

static void	get_collision(t_data *data, t_coll *coll, float dirx, float diry)
{
	float	xo;
	float	yo;

	if (dirx < 0)
		xo = -0.25;
	else
		xo = 0.25;
	if (diry < 0)
		yo = -0.25;
	else
		yo = 0.25;
	coll->ipx = data->player.x;
	coll->ipx_add_xo = (data->player.x + xo);
	coll->ipx_sub_xo = (data->player.x - xo);
	coll->ipy = data->player.y;
	coll->ipy_add_yo = (data->player.y + yo);
	coll->ipy_sub_yo = (data->player.y - yo);
}

void	forward_move_hook(t_data *data, t_coll *coll)
{
	t_player	*p;

	p = &data->player;
	get_collision(data, coll, data->player.dirx, data->player.diry);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || \
		mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		if (data->map[(int)coll->ipy][(int)coll->ipx_add_xo] == 0)
			p->x += (0.01 * SPEED) * p->dirx;
		if (data->map[(int)coll->ipy_add_yo][(int)coll->ipx] == 0)
			p->y += (0.01 * SPEED) * p->diry;
		if (data->minimap == true)
		{
			p->img->instances->x = p->x * data->mms - data->mms / 8;
			p->img->instances->y = p->y * data->mms - data->mms / 8;
		}
	}
}

void	back_move_hook(t_data *data, t_coll *coll)
{
	t_player	*p;

	p = &data->player;
	get_collision(data, coll, data->player.dirx, data->player.diry);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || \
		mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		if (data->map[(int)coll->ipy][(int)coll->ipx_sub_xo] == 0)
			p->x -= (0.01 * SPEED) * p->dirx;
		if (data->map[(int)coll->ipy_sub_yo][(int)coll->ipx] == 0)
			p->y -= (0.01 * SPEED) * p->diry;
		if (data->minimap == true)
		{
			p->img->instances->x = p->x * data->mms - data->mms / 8;
			p->img->instances->y = p->y * data->mms - data->mms / 8;
		}
	}
}

void	left_move_hook(t_data *data, t_coll *coll)
{
	t_player	*p;

	p = &data->player;
	get_collision(data, coll, data->player.lrx, data->player.lry);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->map[(int)coll->ipy][(int)coll->ipx_add_xo] == 0)
			p->x += (0.01 * SPEED) * p->lrx;
		if (data->map[(int)coll->ipy_add_yo][(int)coll->ipx] == 0)
			p->y += (0.01 * SPEED) * p->lry;
		if (data->minimap == true)
		{
			p->img->instances->x = p->x * data->mms - data->mms / 8;
			p->img->instances->y = p->y * data->mms - data->mms / 8;
		}
	}
}

void	right_move_hook(t_data *data, t_coll *coll)
{
	t_player	*p;

	p = &data->player;
	get_collision(data, coll, data->player.lrx, data->player.lry);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->map[(int)coll->ipy][(int)coll->ipx_sub_xo] == 0)
			p->x -= (0.01 * SPEED) * p->lrx;
		if (data->map[(int)coll->ipy_sub_yo][(int)coll->ipx] == 0)
			p->y -= (0.01 * SPEED) * p->lry;
		if (data->minimap == true)
		{
			p->img->instances->x = p->x * data->mms - data->mms / 8;
			p->img->instances->y = p->y * data->mms - data->mms / 8;
		}
	}
}
