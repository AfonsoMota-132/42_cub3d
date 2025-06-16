/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:30:03 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 12:56:56 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

int	get_wall_dir(int side, int stepX, int stepY)
{
	if (side == 0)
	{
		if (stepX > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (stepY > 0)
			return (2);
		else
			return (3);
	}
}

void	ft_player_rot(t_data *data)
{
	if (data->mov->lookl)
	{
		data->mov->mov = true;
		data->player->angle = ft_add_angle(data->player->angle, -2.5);
		data->player->y_look = cos(data->player->angle * M_PI / 180.0);
		data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	}
	if (data->mov->lookr)
	{
		data->mov->mov = true;
		data->player->angle = ft_add_angle(data->player->angle, 2.5);
		data->player->y_look = cos(data->player->angle * M_PI / 180.0);
		data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	}
}

void	ft_ray_dir(t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (ray->posx - ray->mapx)
			* ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - ray->posx)
			* ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (ray->posy - ray->mapy)
			* ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - ray->posy)
			* ray->deltadisty;
	}
}

void	ft_set_ray_loop(t_ray *ray, int x)
{
	ray->camerax = (2 * x / (double)WIN_WIDTH - 1)
		* ((double)WIN_WIDTH / WIN_HEIGHT);
	ray->raydirx = ray->dirx + ray->planex
		* ray->camerax;
	ray->raydiry = ray->diry + ray->planey
		* ray->camerax;
	ray->mapx = (int) ray->posx;
	ray->mapy = (int) ray->posy;
	ray->hit = 0;
	ray->deltadistx = fabs(1 / (ray->raydirx
				+ (ray->raydirx == 0) * 1e-30));
	ray->deltadisty = fabs(1 / (ray->raydiry
				+ (ray->raydiry == 0) * 1e-30));
}

void	ft_pre_render_loop(t_data *data, t_ray *ray, t_player *player)
{
	while (ft_get_time_in_ms() <= data->time_frame)
		;
	data->time_frame += 17;
	data->frame_time = ft_get_time_in_ms() - data->old_frame;
	ft_player_mov(data);
	ray->dirx = player->x_look;
	ray->diry = player->y_look;
	ray->posx = player->x_pos;
	ray->posy = player->y_pos;
	ray->planex = ray->diry * 0.66;
	ray->planey = -ray->dirx * 0.66;
}
