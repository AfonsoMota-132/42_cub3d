/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_mov_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:49:46 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:50:19 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

int	ft_ver_col(char **map, double tempx, double tempy, char except)
{
	if (map[(int)(tempx - 0.05)][(int)(tempy - 0.05)] == 'R'
		|| map[(int)(tempx + 0.05)][(int)(tempy + 0.05)] == 'R'
		|| map[(int)tempx][(int)tempy] == 'R')
		return (2);
	if ((map[(int)(tempx - 0.1)][(int)(tempy - 0.1)] != '1'
		&& map[(int)(tempx + 0.1)][(int)(tempy + 0.1)] != '1'
		&& !(map[(int)(tempx - 0.1)][(int)(tempy - 0.1)] >= 'A'
			&& map[(int)(tempx - 0.1)][(int)(tempy - 0.1)] <= 'K')
		&& map[(int)(tempx + 0.1)][(int)(tempy + 0.1)] != '1'
		&& !(map[(int)(tempx + 0.1)][(int)(tempy + 0.1)] >= 'A'
			&& map[(int)(tempx + 0.1)][(int)(tempy + 0.1)] <= 'K')
		&& map[(int)tempx][(int)tempy] != '1'
		&& !(map[(int)tempx][(int)tempy] >= 'A'
		&& map[(int)tempx][(int)tempy] <= 'K'))
		|| map[(int)tempx][(int)tempy] == except
		|| map[(int)tempx][(int)tempy] == '0')
		return (true);
	return (false);
}

void	ft_player_mov_utils(t_data *data)
{
	if (data->mov->mov && data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos] != 'E')
		data->map[(int) data->player->x_pos] \
			[(int) data->player->y_pos] = 'P';
	if (data->map[(int) data->player->x_pos + 1] \
			[(int) data->player->y_pos] == 'P')
		data->map[(int) data->player->x_pos + 1] \
			[(int) data->player->y_pos] = '0';
	if (data->map[(int) data->player->x_pos - 1] \
		[(int) data->player->y_pos] == 'P')
		data->map[(int) data->player->x_pos - 1] \
		[(int) data->player->y_pos] = '0';
	if (data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos + 1] == 'P')
		data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos + 1] = '0';
	if (data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos - 1] == 'P')
		data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos - 1] = '0';
}
