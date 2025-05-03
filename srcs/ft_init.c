/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:40:02 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/01 16:27:11 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

double ft_get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

t_data	*ft_data_init(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->img = malloc(sizeof(t_img));
	ft_set_img_def(data->img);
	data->ray = malloc(sizeof(t_ray));
	// ft_init_ray(data->ray);

	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->hex_ceiling = 0x000000;
	data->hex_floor = 0xFFFFFF;
	data->mlx = NULL;
	data->win = NULL;

	data->map = malloc(sizeof(char *) * 7);
	data->map[0] = ft_strdup("1111111");
	data->map[1] = ft_strdup("1010101");
	data->map[2] = ft_strdup("1000001");
	data->map[3] = ft_strdup("1000001");
	data->map[4] = ft_strdup("100N001");
	data->map[5] = ft_strdup("1111111");
	data->map[6] = NULL;

	data->mov = malloc(sizeof(t_mov));
	data->mov->mov_f = false;
	data->mov->mov_b = false;
	data->mov->mov_l = false;
	data->mov->mov_r = false;
	data->mov->lookl = false;
	data->mov->lookr = false;
	data->player = malloc(sizeof(t_player));
	data->player->x_pos = 4.5;
	data->player->y_pos = 3.5;
	data->player->angle = 300;
	data->player->y_look = cos(data->player->angle * M_PI / 180.0);
	data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	// printf("x_look %f\ty_look %f\n", data->player->x_look, data->player->y_look);
	data->time_frame = ft_get_time_in_ms() + 17;
	printf("%f\n", data->time_frame);
	return (data);
}

void	ft_set_img_def(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}


