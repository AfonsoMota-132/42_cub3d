/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:48:16 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/13 09:59:36 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int mouse_move(int x, int y, t_data *data)
{
	data->mov->mouse = 0;
	if (x < (WIN_WIDTH >> 1) - 10)
		data->mov->mouse = x - (WIN_WIDTH >> 1);
	if (x > (WIN_WIDTH >> 1)+ 10)
		data->mov->mouse = x - (WIN_WIDTH >> 1);
	(void) y;
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH >> 1, WIN_HEIGHT >> 1);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = ft_data_init(av[1]);
		mlx_hook(data->win, 2, 1L << 0, &key_hook_press, data);
		mlx_hook(data->win, 3, 1L << 1, &key_hook_relea, data);
		mlx_hook(data->win, 6, 1L << 6, &mouse_move, data);
		mlx_do_key_autorepeatoff(data->mlx);
		mlx_mouse_move(data->mlx, data->win, WIN_HEIGHT >> 1, WIN_WIDTH >> 1);
		mlx_loop_hook(data->mlx, &ft_frame_render, data);
		mlx_loop(data->mlx);
	}
	else
		return (ft_putstr_fd("Error: Wrong Number of Arguments\n", 1), 1);
}
