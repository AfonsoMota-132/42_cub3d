/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:22:43 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:22:51 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_first_render_loop(t_thread_data *tdata, int x, int end)
{
	while (++x <= end)
	{
		ft_pre_render_loop(tdata->ray, tdata->data->player, tdata->data);
		ft_set_ray_loop(tdata->ray, x, tdata->data);
		ft_ray_dir(tdata->ray);
		ft_dda(tdata->ray, tdata->data, -1);
		tdata->data->zbuffer[x] = tdata->ray->perpWallDist;
		ft_line_height(tdata->ray, tdata->data);
		ft_pre_render_line(tdata->data, tdata->ray, x);
	}
}

void	ft_render_door(t_thread_data *tdata, int x, int end)
{
	while (++x <= end)
	{
		ft_pre_render_loop(tdata->ray, tdata->data->player, tdata->data);
		ft_set_ray_loop(tdata->ray, x, tdata->data);
		ft_ray_dir(tdata->ray);
		ft_dda(tdata->ray, tdata->data, 'H');
		if (tdata->ray->hit == 2)
		{
			tdata->data->zbuffer[x] = tdata->ray->perpWallDist;
			ft_line_height(tdata->ray, tdata->data);
			ft_pre_render_line(tdata->data, tdata->ray, x);
		}
	}
}

void	*ft_thread_render(void *arg)
{
	t_thread_data	*tdata;
	int				x;

	tdata = (t_thread_data *)arg;
	x = tdata->start_x - 1;
	tdata->ray->drawEnd = 0;
	tdata->ray->drawStart = 0;
	ft_first_render_loop(tdata, x, tdata->end_x);
	ft_render_door(tdata, x, tdata->end_x);
	return (NULL);
}

void	ft_line_height(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX
				- ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY
				- ray->deltaDistY);
	ray->perpWallDist = ray->perpWallDist / data->scale;
	ray->lineHeight = (int)(data->height / ray->perpWallDist);
	ray->drawStart = -(ray->lineHeight >> 1) + (data->height >> 1) - data->player->angle_y;
	ray->drawEnd   =  (ray->lineHeight >> 1) + (data->height >> 1) - data->player->angle_y;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	if (ray->drawEnd >= data->height)
		ray->drawEnd = data->height - 1;
	if (ray->side == 0)
		ray->orien = (ray->stepX <= 0);
	else
		ray->orien = 2 + (ray->stepY <= 0);
}
