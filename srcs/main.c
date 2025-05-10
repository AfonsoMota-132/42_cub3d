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

// int	ft_mouse_hook(int key, t_data *data)
// {
// 	if (key == 1)
// 		data->mov->shoot = 1;
// 	return (0);
// }
//
// int	ft_mouse_release(int key, t_data *data)
// {
// 	if (key == 1)
// 		data->mov->shoot = 2;
// 	return (0);
// }
int	main(void)
{
	t_data	*data;

	system("paplay sound_effects/hope.wav &");
	data = ft_data_init();
	mlx_hook(data->win, 2, 1L << 0, &key_hook_press, data);
	mlx_hook(data->win, 3, 1L << 1, &key_hook_relea, data);
	mlx_hook(data->win, 6, 1L << 6, &mouse_move, data);
	// mlx_hook(data->win, 4, 1L << 2, &ft_mouse_hook, data);
	// mlx_hook(data->win, 5, 1L << 3, &ft_mouse_release, data);
	mlx_mouse_move(data->mlx, data->win, WIN_HEIGHT / 2, WIN_WIDTH / 2);
	mlx_loop_hook(data->mlx, &ft_frame_render, data);
	mlx_loop(data->mlx);
	ft_free(0, data);
}
