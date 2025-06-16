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
