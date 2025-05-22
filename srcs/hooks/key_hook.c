/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:23:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/06 09:33:36 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	key_hook_press(int key, t_data *data)
{
	if (key == 65307 && !data->mov->pause)
		data->mov->pause = true;
	else if (key == 65307 && data->mov->pause)
		data->mov->pause = false;
	if (key == 119)
		data->mov->mov_f = true;
	if (key == 97)
		data->mov->mov_l = true;
	if (key == 115)
		data->mov->mov_b = true;
	if (key == 100)
		data->mov->mov_r = true;
	if (key == 65361)
		data->mov->lookl = true;
	if (key == 65363)
		data->mov->lookr = true;
	if (key == 32 && !data->mov->shoot)
		data->mov->shoot = true;
	if (key == 101)
		data->mov->open = true;
	return (0);
}

int	key_hook_relea(int key, t_data *data)
{
	if (key == 65307)
		data->mov->exit = true;
	if (key == 119)
		data->mov->mov_f = false;
	if (key == 97)
		data->mov->mov_l = false;
	if (key == 115)
		data->mov->mov_b = false;
	if (key == 100)
		data->mov->mov_r = false;
	if (key == 65361)
		data->mov->lookl = false;
	if (key == 65363)
		data->mov->lookr = false;
	if (key == 101)
		data->mov->open = false;
	return (0);
}
