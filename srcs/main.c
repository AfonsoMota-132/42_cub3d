/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:48:16 by afogonca          #+#    #+#             */
/*   Updated: 2025/04/26 09:55:07 by afogonca         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	get_wall_dir(int side, int stepX, int stepY)
{
	if (side == 0)
	{
		if (stepX > 0)
			return (0);  // Ray moved right (+X), hit West wall
		else
			return (1);  // Ray moved left (-X), hit East wall
	}
	else
	{
		if (stepY > 0)
			return (2); // Ray moved down (+Y), hit North wall
		else
			return (3); // Ray moved up (-Y), hit South wall
	}
}

int	key_hook_relea(int key, t_data *data)
{
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
	return (0);
}

int	main(void)
{
	t_data *data;

	data = ft_data_init();
	mlx_hook(data->win, 2, 1L<<0, &key_hook_press, data);
	mlx_hook(data->win, 3, 1L<<1, &key_hook_relea, data);
	mlx_loop_hook(data->mlx, &ft_frame_render, data);
	mlx_loop(data->mlx);
}
