/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_mov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:27:42 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:50:14 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_player_mov(t_data *data)
{
	ft_player_rot(data);
	ft_player_mov_f(data);
	ft_player_mov_b(data);
	ft_player_mov_l(data);
	ft_player_mov_r(data);
	if ((data->mov->mov && data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos] != 'E') || (data->mov->mov
			&& data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos] != 'P'))
		ft_player_mov_utils(data);
}

void	ft_player_mov_b(t_data *data)
{
	double	tempx;
	double	tempy;

	if (data->mov->mov_b && !data->mov->mov_f)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos - data->player->x_look
			* (0.003012 * data->frame_time);
		tempy = data->player->y_pos - data->player->y_look
			* (0.003012 * data->frame_time);
		if (ft_ver_col(data->map, tempx, data->player->y_pos, 'P') == 1)
			data->player->x_pos = tempx;
		if (ft_ver_col(data->map, data->player->x_pos, tempy, 'P') == 1)
			data->player->y_pos = tempy;
		if (ft_ver_col(data->map, tempx, data->player->y_pos, 'P') == 2)
		{
			data->player1->x_pos = data->portal->x_pos;
			data->player1->y_pos = data->portal->y_pos;
		}
		if (ft_ver_col(data->map, data->player->x_pos, tempy, 'P') == 2)
		{
			data->player1->x_pos = data->portal->x_pos;
			data->player1->y_pos = data->portal->y_pos;
		}
	}
}

void	ft_player_mov_f(t_data *data)
{
	double	tempx;
	double	tempy;

	if (data->mov->mov_f && !data->mov->mov_b)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos + data->player->x_look
			* (0.003012 * data->frame_time);
		tempy = data->player->y_pos + data->player->y_look
			* (0.003012 * data->frame_time);
		if (ft_ver_col(data->map, tempx, data->player->y_pos, 'P') == 1)
			data->player->x_pos = tempx;
		if (ft_ver_col(data->map, data->player1->x_pos, tempy, 'P') == 1)
			data->player->y_pos = tempy;
		if (ft_ver_col(data->map, tempx, data->player1->y_pos, 'P') == 2)
		{
			data->player1->x_pos = data->portal->x_pos;
			data->player1->y_pos = data->portal->y_pos;
		}
		if (ft_ver_col(data->map, data->player1->x_pos, tempy, 'P') == 2)
		{
			data->player1->x_pos = data->portal->x_pos;
			data->player1->y_pos = data->portal->y_pos;
		}
	}
}

void	ft_player_mov_r(t_data *data)
{
	double	tempx;
	double	tempy;

	if (data->mov->mov_r && !data->mov->mov_l)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos + data->ray->planeX
			* (0.003012 * data->frame_time);
		tempy = data->player->y_pos + data->ray->planeY
			* (0.003012 * data->frame_time);
		if (ft_ver_col(data->map, tempx, data->player->y_pos, 'P') == 1)
			data->player->x_pos = tempx;
		if (ft_ver_col(data->map, data->player->x_pos, tempy, 'P') == 1)
			data->player->y_pos = tempy;
		if (ft_ver_col(data->map, tempx, data->player1->y_pos, 'P') == 2)
		{
			data->player1->x_pos = data->portal->x_pos;
			data->player1->y_pos = data->portal->y_pos;
		}
		if (ft_ver_col(data->map, data->player1->x_pos, tempy, 'P') == 2)
		{
			data->player1->x_pos = data->portal->x_pos;
			data->player1->y_pos = data->portal->y_pos;
		}
	}
}

void	ft_player_mov_l(t_data *data)
{
	double	tempx;
	double	tempy;

	if (data->mov->mov_l && !data->mov->mov_r)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos - data->ray->planeX
			* (0.003012 * data->frame_time);
		tempy = data->player->y_pos - data->ray->planeY
			* (0.003012 * data->frame_time);
		if (ft_ver_col(data->map, tempx, data->player->y_pos, 'P') == 1)
			data->player->x_pos = tempx;
		if (ft_ver_col(data->map, data->player->x_pos, tempy, 'P') == 1)
			data->player->y_pos = tempy;
		if (ft_ver_col(data->map, tempx, data->player1->y_pos, 'P') == 2)
		{
			data->player1->x_pos = data->portal->x_pos;
			data->player1->y_pos = data->portal->y_pos;
		}
		if (ft_ver_col(data->map, data->player1->x_pos, tempy, 'P') == 2)
		{
			data->player1->x_pos = data->portal->x_pos;
			data->player1->y_pos = data->portal->y_pos;
		}
	}
}
