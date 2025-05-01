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

int	key_hook(int key, void *idk)
{
	if (key == 65307)
		exit(0);
	(void) idk;
	return (0);
}

int	main(void)
{
	t_data *data;

	data = ft_data_init();
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3d");
	ft_frame_render(data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_loop(data->mlx);
}
