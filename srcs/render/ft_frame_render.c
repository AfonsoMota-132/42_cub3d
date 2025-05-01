/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:49:26 by afogonca          #+#    #+#             */
/*   Updated: 2025/04/26 09:54:48 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	ft_frame_render(t_data *data)
{
	int	y;
	int x;

	y = -1;
	data->img->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->pixel_bits,
			&data->img->size_line, &data->img->endian);
	while (++y < data->win_height)
	{
		x = -1;
		while (++x < data->win_width)
		{
			if (y > data->win_height / 2)
				set_image_pixel(data->img, x, y, data->hex_ceiling);
			else if (y <= data->win_height / 2)
				set_image_pixel(data->img, x, y, data->hex_floor);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	init_texture_pixels(t_data *data)
{
	int	i;

	data->tex_pix = ft_calloc(data->win_height + 1,
			sizeof * data->tex_pix);
	i = 0;
	while (i < data->win_height)
	{
		data->tex_pix[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pix);
		i++;
	}
}

