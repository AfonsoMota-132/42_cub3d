/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:48:16 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/22 08:48:18 by afogonca         ###   ########.fr       */
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
	int	x = 2;
	int	y = 2;
	char	*map[] = {"11111", "10001", "10P01", "10001", "11111"};
	void	*mlx;
	void	*win;


	/*mlx = mlx_init();*/
	/*win = mlx_new_window(mlx, 1280, 720, "cub3d");*/
	mlx_hook(win, KeyPress, KeyPressMask, &key_hook, win);
	mlx_loop(mlx);
}
