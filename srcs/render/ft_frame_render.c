/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:49:26 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:25:58 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_raycasting_enemies_utils3(t_data *data, t_enemy *enemy)
{
	if ((data->map[(int) enemy->data->x_pos] \
		[(int) enemy->data->y_pos] != 'A'))
	{
		if (data->map[(int) enemy->data->x_pos] \
			[(int) enemy->data->y_pos] != 'P')
			data->map[(int) enemy->data->x_pos] \
			[(int) enemy->data->y_pos] = enemy->map;
		if (data->map[(int) enemy->data->x_pos + 1] \
			[(int) enemy->data->y_pos] == enemy->map)
			data->map[(int) enemy->data->x_pos + 1] \
				[(int) enemy->data->y_pos] = '0';
		if (data->map[(int) enemy->data->x_pos - 1] \
			[(int) enemy->data->y_pos] == enemy->map)
			data->map[(int) enemy->data->x_pos - 1] \
			[(int) enemy->data->y_pos] = '0';
		if (data->map[(int) enemy->data->x_pos] \
				[(int) enemy->data->y_pos + 1] == enemy->map)
			data->map[(int) enemy->data->x_pos] \
				[(int) enemy->data->y_pos + 1] = '0';
		if (data->map[(int) enemy->data->x_pos] \
			[(int) enemy->data->y_pos - 1] == enemy->map)
			data->map[(int) enemy->data->x_pos] \
				[(int) enemy->data->y_pos - 1] = '0';
	}
}

void	ft_shoot_raycasting(t_data *data)
{
	t_shoot_rc	sdata;

	sdata.hit = data->width / 2;
	sdata.is_moving = data->mov->mov || data->mov->look;
	if (sdata.is_moving)
		sdata.max_offset = 600;
	else
		sdata.max_offset = 15;
	sdata.spread = (rand() % (2 * sdata.max_offset + 1)) - sdata.max_offset;
	sdata.hit += sdata.spread;
	if (sdata.hit < 0)
		sdata.hit = 0;
	if (sdata.hit >= data->width)
		sdata.hit = data->width - 1;
	ft_pre_render_loop(data->ray, data->player);
	ft_set_ray_loop(data->ray, sdata.hit, data);
	ft_ray_dir(data->ray);
	sdata.enemy = ft_dda_shoot(data->ray, data);
	ft_shoot_raycasting2(data, &sdata);
}

void	ft_render(t_data *data)
{
	int	i;

	data->player = data->player1;
	data->img = data->img_player;
	ft_pre_render_loop(data->ray, data->player);
	i = -1;
	while (++i < data->nbr_threads)
	{
		ft_pre_render_loop(data->tdata[i].ray, data->player);
		pthread_create(&data->thread[i], NULL,
			ft_thread_render, &data->tdata[i]);
	}
	i = -1;
	while (++i < data->nbr_threads)
		pthread_join(data->thread[i], NULL);
	i = -1;
	ft_sort_enemies(data);
	while (data->enemy_arr[++i])
		ft_enemy_render_threads(data->enemy_arr[i]);
	if (data->mov->shoot)
		ft_shoot_raycasting(data);
	ft_put_fps(data);
}

void	ft_frame_render_pause(t_data *data)
{
	int				x;
	int				y;

	x = -1;
	while (++x < data->width)
	{
		y = -1;
		while (++y < data->height)
			data->img_pause->addr[y * data->width + x]
				= ft_pixel_darken(data->img->addr[y * data->width + x], 0.45);
	}
	ft_frame_render_pause_utils(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_pause->img, 0, 0);
}

int	ft_frame_render(t_data *data)
{
	while (ft_get_time_in_ms() <= data->time_frame)
		;
	data->time_frame = ft_get_time_in_ms() + 0;
	data->frame_time = ft_get_time_in_ms() - data->old_frame;
	data->fps = 1000 / (data->frame_time);
	data->old_frame = ft_get_time_in_ms();
	if (!data->mov->pause)
	{
		ft_player_mov(data);
		ft_render(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
		data->mov->mov = false;
		data->mov->look = false;
		data->mov->shoot = false;
	}
	else
		ft_frame_render_pause(data);
	return (0);
}
