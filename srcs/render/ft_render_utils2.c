/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:40:24 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 11:40:54 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_door_handle_utils(t_door *door, t_data *data, bool def)
{
	if (def)
	{
		if (data->mov->open && !door->open && door->pos == 0)
			door->open = 1;
		else if (data->mov->open && !door->open)
			door->open = 2;
	}
	if (door->open == 1)
		door->pos += 0.0000015 * data->frame_time;
	else if (door->open == 2)
		door->pos -= 0.0000015 * data->frame_time;
	if (door->pos <= 0)
	{
		door->open = 0;
		door->pos = 0;
	}
	if (door->pos >= 1)
	{
		door->open = 0;
		door->pos = 1;
	}
}

double	ft_add_angle(double angle, double delta)
{
	angle += delta;
	if (angle >= 360.0)
		angle -= 360.0;
	else if (angle < 0.0)
		angle += 360.0;
	return (angle);
}

double	ft_door_state(t_data *data, int x, int y)
{
	t_door	*door;

	door = data->head_door;
	while (door)
	{
		if (door->y_pos == y
			&& door->x_pos == x)
			return (door->pos);
		door = door->next;
	}
	return (1);
}
