/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_mov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:27:42 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/06 09:30:53 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_player_mov(t_data *data)
{
	ft_player_rot(data);
	ft_player_mov_fb(data);
	ft_player_mov_lr(data);
	if ((data->mov->mov && data->map[(int) data->player->x_pos][ (int) data->player->y_pos] != 'E')
	|| (data->mov->mov && data->map[(int) data->player->x_pos][ (int) data->player->y_pos] != 'P'))
	{
		if (data->mov->mov && data->map[(int) data->player->x_pos][ (int) data->player->y_pos] != 'E')
			data->map[(int) data->player->x_pos][(int) data->player->y_pos] = 'P';
		if (data->map[(int) data->player->x_pos + 1][(int) data->player->y_pos] == 'P')
			data->map[(int) data->player->x_pos + 1][(int) data->player->y_pos] = '0';
		if (data->map[(int) data->player->x_pos - 1][(int) data->player->y_pos] == 'P')
			data->map[(int) data->player->x_pos - 1][(int) data->player->y_pos] = '0';	
		if (data->map[(int) data->player->x_pos][(int) data->player->y_pos + 1] == 'P')
			data->map[(int) data->player->x_pos][(int) data->player->y_pos + 1] = '0';
		if (data->map[(int) data->player->x_pos][(int) data->player->y_pos - 1] == 'P')
			data->map[(int) data->player->x_pos][(int) data->player->y_pos - 1] = '0';
	}
	if (data->mov->mov && ft_get_time_in_ms() >= data->mov->time_sound)
	{
		if (data->mov->sound == 0)
		{
			system("paplay sound_effects/Concrete1.wav &");
			data->mov->sound++;
		}
		if (data->mov->sound == 1)
		{
			system("paplay sound_effects/Concrete2.wav &");
			data->mov->sound--;
		}
		data->mov->time_sound = ft_get_time_in_ms() + 500;
	}
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
		if (ft_ver_col(data->map, tempx, data->player->y_pos))
			data->player->x_pos = tempx;
		if (ft_ver_col(data->map, data->player->x_pos, tempy))
			data->player->y_pos = tempy;
	}
	if (data->mov->mov_b && !data->mov->mov_f)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos - data->player->x_look * 0.05;
		tempy = data->player->y_pos - data->player->y_look * 0.05;
		if (ft_ver_col(data->map, tempx, data->player->y_pos))
			data->player->x_pos = tempx;
		if (ft_ver_col(data->map, data->player->x_pos, tempy))
			data->player->y_pos = tempy;
	}
}

void	ft_player_mov_lr(t_data *data)
{
	double	tempx;
	double	tempy;

	if (data->mov->mov_l && !data->mov->mov_r)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos - data->ray->planeX * 0.05;
		tempy = data->player->y_pos - data->ray->planeY * 0.05;
		if (ft_ver_col(data->map, tempx, data->player->y_pos))
			data->player->x_pos = tempx;
		if (ft_ver_col(data->map, data->player->x_pos, tempy))
			data->player->y_pos = tempy;
	}
	if (data->mov->mov_r && !data->mov->mov_l)
	{
		data->mov->mov = true;
		tempx = data->player->x_pos + data->ray->planeX * 0.05;
		tempy = data->player->y_pos + data->ray->planeY * 0.05;
		if (ft_ver_col(data->map, tempx, data->player->y_pos))
			data->player->x_pos = tempx;
		if (ft_ver_col(data->map, data->player->x_pos, tempy))
			data->player->y_pos = tempy;
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
