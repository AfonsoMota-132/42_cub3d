/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:48:16 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 09:45:12 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	ft_kill(t_data *data)
{
	ft_free(1, data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		if (access(av[1], F_OK | W_OK) == -1)
		{
			ft_putstr_fd("Error\nFile doesnt exist/no perms!\n", 2);
			exit (1);
		}
		data = ft_data_init(av[1]);
		mlx_hook(data->win, 2, 1L << 0, &key_hook_press, data);
		mlx_hook(data->win, 3, 1L << 1, &key_hook_relea, data);
		mlx_hook(data->win, 6, 1L << 6, &mouse_move, data);
		mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_kill, data);
		mlx_do_key_autorepeatoff(data->mlx);
		mlx_loop_hook(data->mlx, &ft_frame_render, data);
		mlx_loop(data->mlx);
	}
	else
		return (ft_putstr_fd("Error: Wrong Number of Arguments\n", 2), 1);
}

double	ft_get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0));
}
