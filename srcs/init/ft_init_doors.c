/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:14:39 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 11:38:29 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	ft_init_player_utils(t_data *data, char tmp, int i)
{
	if (tmp && data->player->x_pos == -1
		&& data->player->y_pos == -1)
	{
		data->player->x_pos = i + 0.5;
		data->player->y_pos = ft_strchr_len(data->map->map[i], tmp) + 0.5;
		data->player->angle = (tmp == 'N') * 270 + (tmp == 'S') * 90
			+ (tmp == 'W') * 180;
		data->player->y_look = cos(data->player->angle * M_PI / 180.0);
		data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	}
	else if (tmp)
	{
		ft_putstr_fd("Error\nMultiple Players\n", 2);
		ft_free(1, data);
	}
}

t_door	*ft_new_door(int x, int y)
{
	t_door	*new;

	new = malloc(sizeof(t_door));
	new->next = NULL;
	new->open = 0;
	new->pos = 0;
	new->seen = false;
	new->x_pos = x;
	new->y_pos = y;
	return (new);
}

void	ft_door_add_back(t_door **door, int x, int y)
{
	t_door	*tmp;

	if (!*door)
		*door = ft_new_door(x, y);
	tmp = *door;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_new_door(x, y);
}

void	ft_init_doors(t_data *data)
{
	int	y;
	int	x;

	x = -1;
	while (data->map->map[++x])
	{
		y = -1;
		while (data->map->map[x][++y])
		{
			if (data->map->map[x][y] == 'H')
				ft_door_add_back(&data->head_door, x, y);
		}
	}
}
