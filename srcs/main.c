/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:48:16 by afogonca          #+#    #+#             */
/*   Updated: 2025/04/25 17:11:34 by afogonca         ###   ########.pt       */
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

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

int	main(void)
{
	t_data *data;

	data = ft_data_init();
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3d");

	data->img = malloc(sizeof(t_img));
	data->img->img = NULL;
	data->img->addr = NULL;
	data->img->pixel_bits = 0;
	data->img->size_line = 0;
	data->img->endian = 0;
	data->img->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->pixel_bits,
			&data->img->size_line, &data->img->endian);
	for (int y =0;y < data->win_height; y++)
		for (int x =0;x < data->win_width; x++)
		{
			if (y > data->win_height / 2)
				set_image_pixel(data->img, x, y, data->hex_ceiling);
			else if (y <= data->win_height / 2)
				set_image_pixel(data->img, x, y, data->hex_floor);
		}
	
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_hook(data->win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_loop(data->mlx);
}
