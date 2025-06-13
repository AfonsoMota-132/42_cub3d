/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:49:26 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/13 10:56:27 by afogonca         ###   ########.fr       */
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
	ray->orien = get_wall_dir(ray->side, ray->stepX,
			ray->stepY);
}

void	ft_render_loop(t_data *data, int x, int door)
{
	while (++x < WIN_WIDTH)
	{
		ft_set_ray_loop(data->ray, x);
		ft_ray_dir(data->ray);
		ft_dda(data, door);
		ft_line_height(data->ray);
		ft_pre_render_line(data, x, -1);
	}
}

int	ft_frame_render(t_data *data)
{
	if (data->mov->exit)
	{
		mlx_loop_end(data->mlx);
		data->mov->exit_main = true;
		return (1);
	}
	ft_pre_render_loop(data, data->ray, data->player);
	ft_render_loop(data, -1, 0);
	ft_render_loop(data, -1, 1);
	ft_render_minimap(data);
	data->mov->mov = false;
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

void	ft_dda(t_data *data, int door)
{
	while (data->ray->hit == 0)
	{
		if (data->ray->sideDistX < data->ray->sideDistY)
		{
			data->ray->sideDistX += data->ray->deltaDistX;
			data->ray->mapX += data->ray->stepX;
			data->ray->side = 0;
		}
		else
		{
			data->ray->sideDistY += data->ray->deltaDistY;
			data->ray->mapY += data->ray->stepY;
			data->ray->side = 1;
		}
		if (door && data->map->map[data->ray->mapX][data->ray->mapY] == 'H')
			data->ray->hit = 2;
		else if (data->map->map[data->ray->mapX][data->ray->mapY] == '1')
			data->ray->hit = 1;
	}
}
