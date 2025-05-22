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
	if (x < (data->width >> 1) - 10)
		data->mov->lookml = idk;
	if (x > (data->width >> 1)+ 10)
		data->mov->lookmr = idk;
	if (!data->mov->pause)
		mlx_mouse_move(data->mlx, data->win, data->width / 2, data->height / 2);
	(void) y;
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

int mouse_handler(int button, int x, int y, t_data *data)
{
    if (button == 1 && data->mov->pause) // left click
    {
        // if (x >= 621 && x <= 657 && y >= 484 && y <= 618)
		mlx_loop_end(data->mlx);
    }
	else if (!data->mov->pause)
	{
		if (button == 1)
			data->mov->shoot = true;
	}
	(void) x;
	(void) y;
    return (0);
	(void) data;
}
int	main(void)
{
	t_data	*data;

	data = ft_data_init();
	for (int y = 0; data->bigmap[y]; y++)
		printf("%s\n", data->bigmap[y]);
	mlx_hook(data->win, 2, 1L << 0, &key_hook_press, data);
	mlx_hook(data->win, 3, 1L << 1, &key_hook_relea, data);
	mlx_hook(data->win, 6, 1L << 6, &mouse_move, data);
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_mouse_hook(data->win, mouse_handler, data);
	mlx_mouse_move(data->mlx, data->win, data->height >> 1, data->width >> 1);
	mlx_loop_hook(data->mlx, &ft_frame_render, data);
	mlx_loop(data->mlx);
	mlx_do_key_autorepeaton(data->mlx);
	
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	data->width = 1920;
	data->height = 1080;
	ft_win_start(data);
	int	i = -1;
	while (++i < data->nbr_threads)
	{
	   	data->tdata[i].start_x = i * data->width / data->nbr_threads;
	   	data->tdata[i].end_x = (i + 1) * data->width / data->nbr_threads;
	}
	ft_render(data);
	mlx_hook(data->win, 2, 1L << 0, &key_hook_press, data);
	mlx_hook(data->win, 3, 1L << 1, &key_hook_relea, data);
	mlx_hook(data->win, 6, 1L << 6, &mouse_move, data);
	mlx_mouse_hook(data->win, mouse_handler, data);
	mlx_mouse_move(data->mlx, data->win, data->height >> 1, data->width >> 1);
	mlx_loop_hook(data->mlx, &ft_frame_render, data);
	mlx_loop(data->mlx);
	// ft_free(0, data);
}
