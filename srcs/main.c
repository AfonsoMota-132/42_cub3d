/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:48:16 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/06 09:34:33 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"
int mouse_move(int x, int y, t_data *data)
{
	int	idk = 3;
	if (y < WIN_HEIGHT / 2 - 20)
		data->mov->lookmu = idk;
	if (y > WIN_HEIGHT / 2 + 20)
		data->mov->lookmd = idk;
	if (x < WIN_WIDTH / 2 - 10)
		data->mov->lookml = idk;
	if (x > WIN_WIDTH / 2 + 10)
		data->mov->lookmr = idk;
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	(void) x;
	(void) y;
	(void) data;
	return (1);
}

int	main(void)
{
	t_data	*data;

	data = ft_data_init();
	mlx_hook(data->win, 2, 1L << 0, &key_hook_press, data);
	mlx_hook(data->win, 3, 1L << 1, &key_hook_relea, data);
	mlx_hook(data->win, 6, 1L << 6, &mouse_move, data);
	mlx_mouse_move(data->mlx, data->win, WIN_HEIGHT / 2, WIN_WIDTH / 2);
	mlx_loop_hook(data->mlx, &ft_frame_render, data);
	mlx_loop(data->mlx);
    ft_free(0, data);
}
