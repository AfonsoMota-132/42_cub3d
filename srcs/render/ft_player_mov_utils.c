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

int	ft_ver_col(double tempx, double tempy, char except, t_data *data)
{
	int	i;

	if (data->bigmap[(int)tempx][(int)tempy] == 'H')
	{
		i = -1;
		while (data->door[++i])
		{
			printf("x1 %i\ty1 %i\tx2 %d\ty2 %d\n", (int)(tempx / data->scale),
			(int) (tempy / data->scale), data->door[i]->x_pos, data->door[i]->y_pos);
			if (((int) (tempx / data->scale) == (int) data->door[i]->x_pos)
				&& (((int) (tempy / data->scale) == (int) data->door[i]->y_pos)))
			{
				break ;
			}
		}
		printf("wtf %f\n", data->door[i]->pos);
		if (data->door[i]
			&& data->door[i]->pos >= 0.8)
		{
			return (true);
		}
		else
			return (false);
	}
	if ((data->bigmap[(int)(tempx - 0.1)][(int)(tempy - 0.1)] != '1'
		&& data->bigmap[(int)(tempx + 0.1)][(int)(tempy + 0.1)] != '1'
		&& !(data->bigmap[(int)(tempx - 0.1)][(int)(tempy - 0.1)] >= 'A'
			&& data->bigmap[(int)(tempx - 0.1)][(int)(tempy - 0.1)] <= 'K')
		&& data->bigmap[(int)(tempx + 0.1)][(int)(tempy + 0.1)] != '1'
		&& !(data->bigmap[(int)(tempx + 0.1)][(int)(tempy + 0.1)] >= 'A'
			&& data->bigmap[(int)(tempx + 0.1)][(int)(tempy + 0.1)] <= 'K')
		&& data->bigmap[(int)tempx][(int)tempy] != '1'
		&& !(data->bigmap[(int)tempx][(int)tempy] >= 'A'
		&& data->bigmap[(int)tempx][(int)tempy] <= 'K'))
		|| data->bigmap[(int)tempx][(int)tempy] == except
		|| data->bigmap[(int)tempx][(int)tempy] == '0')
		return (true);
	return (false);
}

void	ft_player_mov_utils(t_data *data)
{
	if (data->mov->mov && data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos] < 'A'
		&& data->mov->mov && data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos] > 'K'
		&& data->mov->mov && data->map[(int) data->player->x_pos] \
		[(int) data->player->y_pos] != 'H')
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
