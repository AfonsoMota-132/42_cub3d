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

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = ft_data_init(av[1]);
		mlx_hook(data->win, 2, 1L << 0, &key_hook_press, data);
		mlx_hook(data->win, 3, 1L << 1, &key_hook_relea, data);
		mlx_loop_hook(data->mlx, &ft_frame_render, data);
		mlx_loop(data->mlx);
	}
	else
		return (ft_putstr_fd("Error: Wrong Number of Arguments\n", 1), 1);
}
