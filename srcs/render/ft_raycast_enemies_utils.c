/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_enemies_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:25:31 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:25:57 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_sort_enemies(t_data *data)
{
	int		i;
	t_enemy	*tmp;
	int		dist1;
	int		dist2;

	tmp = data->enemy_arr[0];
	i = -1;
	while (data->enemy_arr[++i + 1])
	{
		dist1 = sqrt(pow(data->player->x_pos
					- data->enemy_arr[i]->data->x_pos, 2)
				+ pow(data->player->y_pos
					- data->enemy_arr[i]->data->y_pos, 2));
		dist2 = sqrt(pow(data->player->x_pos
					- data->enemy_arr[i + 1]->data->x_pos, 2)
				+ pow(data->player->y_pos
					- data->enemy_arr[i + 1]->data->y_pos, 2));
		if (dist1 < dist2)
		{
			tmp = data->enemy_arr[i];
			data->enemy_arr[i] = data->enemy_arr[i + 1];
			data->enemy_arr[i + 1] = tmp;
			i = -1;
		}
	}
}

void	ft_shoot_raycasting2(t_data *data, t_shoot_rc *sdata)
{
	int	i;

	if (sdata->enemy)
	{
		i = -1;
		while (data->enemy_arr[++i])
		{
			if (data->enemy_arr[i]->map == sdata->enemy)
			{
				data->enemy_arr[i]->map = '0';
				data->map[(int) data->enemy_arr[i]->data->x_pos] \
					[(int) data->enemy_arr[i]->data->y_pos] = '0';
			}
		}
	}
}
