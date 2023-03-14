/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 22:04:17 by ageels        #+#    #+#                 */
/*   Updated: 2023/03/14 13:48:42 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_include/cub.h"

void	forward_move_hook(t_data *data, t_coll *coll)
{
	t_player	*p;

	p = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map[(int)coll->ipy][(int)coll->ipx_add_xo] == 0)
			p->x += SPEED * p->dirx;
		if (data->map[(int)coll->ipy_add_yo][(int)coll->ipx] == 0)
			p->y += SPEED * p->diry;
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map[(int)coll->ipy][(int)coll->ipx_sub_xo] == 0)
			p->x -= SPEED * p->dirx;
		if (data->map[(int)coll->ipy_sub_yo][(int)coll->ipx] == 0)
			p->y -= SPEED * p->diry;
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->map[(int)coll->ipy][(int)coll->ipx_add_xo] == 0)
			p->x += SPEED * p->lrx;
		if (data->map[(int)coll->ipy_add_yo][(int)coll->ipx] == 0)
			p->y += SPEED * p->lry;
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->map[(int)coll->ipy][(int)coll->ipx_sub_xo] == 0)
			p->x -= SPEED * p->lrx;
		if (data->map[(int)coll->ipy_sub_yo][(int)coll->ipx] == 0)
			p->y -= SPEED * p->lry;
		if (data->minimap == true)
		{
			p->img->instances->x = p->x * data->mms - data->mms / 8;
			p->img->instances->y = p->y * data->mms - data->mms / 8;
		}
	}
}
