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

#include "ft_render.h"

void	ft_line_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX
				- ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY
				- ray->deltaDistY);
	ray->lineHeight = (int)(WIN_HEIGHT / ray->perpWallDist);
	ray->drawStart = -(ray->lineHeight >> 1) + (WIN_HEIGHT >> 1);
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = (ray->lineHeight >> 1) + (WIN_HEIGHT >> 1);
	if (ray->drawEnd >= WIN_HEIGHT)
		ray->drawEnd = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->orien = (ray->stepX <= 0);
	else
		ray->orien = 2 + (ray->stepY <= 0);
}

void *thread_render(void *arg)
{
    t_thread_data *tdata = (t_thread_data *)arg;
    int x = tdata->start_x - 1;

    while (++x < tdata->end_x)
    {
        ft_set_ray_loop(tdata->ray, x);
        ft_ray_dir(tdata->ray);
        ft_dda(tdata->ray, tdata->data);
        ft_line_height(tdata->ray);
        ft_pre_render_line(tdata->data, tdata->ray, x, -1);
    }
    return (NULL);
}

int	ft_frame_render(t_data *data)
{
	int	i;

	while (ft_get_time_in_ms() <= data->time_frame)
		;
	data->time_frame = ft_get_time_in_ms() + 16.6;
	data->fps = 1000 / (ft_get_time_in_ms() - data->old_frame);
	data->old_frame = ft_get_time_in_ms();
	ft_player_mov(data);
	i = -1;
	while (data->mov->mov && ++i < data->nbr_threads)
	{
		ft_pre_render_loop(data->tdata[i].ray, data->player);
		pthread_create(&data->thread[i], NULL, thread_render, &data->tdata[i]);
	}
	i = -1;
	while (data->mov->mov && ++i < data->nbr_threads)
		pthread_join(data->thread[i], NULL);
	ft_pre_render_loop(data->tdata[1].ray, data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	char			*str = ft_itoa((int) data->fps);
	mlx_string_put(data->mlx, data->win, 5, 10, 0xFF00FF, str);
	return (0);
}

void	ft_dda(t_ray *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (data->map[ray->mapX][ray->mapY] == '1')
			ray->hit = 1;
	}
}
