/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_mov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:27:42 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 13:23:51 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_player_rotm(t_data *data)
{
	if (data->mov->mouse < 0)
	{
		data->mov->mouse *= -1;
		data->mov->mov = true;
		data->player->angle = ft_add_angle(data->player->angle,
				(int)(-0.05 * data->mov->mouse));
		data->player->y_look = cos(data->player->angle * M_PI / 180.0);
		data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	}
	else
	{
		data->mov->mov = true;
		data->player->angle = ft_add_angle(data->player->angle,
				(int)(0.045 * data->mov->mouse));
		data->player->y_look = cos(data->player->angle * M_PI / 180.0);
		data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	}
}

void	ft_player_mov(t_data *data)
{
	if (!data->mov->mouse)
		ft_player_rot(data);
	else
		ft_player_rotm(data);
	ft_player_mov_fb(data);
	ft_player_mov_lr(data);
}

void	ft_player_mov_fb(t_data *data)
{
	double	tempx;
	double	tempy;

	if (data->mov->mov_f && !data->mov->mov_b)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos + data->player->x_look * 0.05;
		tempy = data->player->y_pos + data->player->y_look * 0.05;
		if (ft_ver_col(data->map->map, tempx, tempy))
		{
			data->player->x_pos = tempx;
			data->player->y_pos = tempy;
		}
	}
	if (data->mov->mov_b && !data->mov->mov_f)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos - data->player->x_look * 0.05;
		tempy = data->player->y_pos - data->player->y_look * 0.05;
		if (ft_ver_col(data->map->map, tempx, tempy))
		{
			data->player->x_pos = tempx;
			data->player->y_pos = tempy;
		}
	}
}

void	ft_player_mov_lr(t_data *data)
{
	double	tempx;
	double	tempy;

	if (data->mov->mov_l && !data->mov->mov_r)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos - data->ray->planex * 0.05;
		tempy = data->player->y_pos - data->ray->planey * 0.05;
		if (ft_ver_col(data->map->map, tempx, tempy))
		{
			data->player->x_pos = tempx;
			data->player->y_pos = tempy;
		}
	}
	if (data->mov->mov_r && !data->mov->mov_l)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos + data->ray->planex * 0.05;
		tempy = data->player->y_pos + data->ray->planey * 0.05;
		if (ft_ver_col(data->map->map, tempx, tempy))
		{
			data->player->x_pos = tempx;
			data->player->y_pos = tempy;
		}
	}
}

bool	ft_ver_col(char **map, double tempx, double tempy)
{
	if (map[(int)(tempx - 0.1)][(int)(tempy - 0.1)] != '1'
		&& map[(int)(tempx + 0.1)][(int)(tempy + 0.1)] != '1'
		&& map[(int)tempx][(int)tempy] != '1'
		&& map[(int)tempx][(int)tempy] != '1')
		return (true);
	return (false);
}
