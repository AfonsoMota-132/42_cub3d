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

void	ft_first_render_loop(t_thread_data *tdata, int x, int end, int rec)
{
	int	first_x;
	int	last_x;

	first_x = 0;
	last_x = 0;
	while (++x < end)
	{
		ft_set_ray_loop(tdata->ray, x, tdata->data);
		ft_ray_dir(tdata->ray);
		ft_dda(tdata->ray, tdata->data, rec);
		if (!rec)
			tdata->data->zbuffer[x] = tdata->ray->perpWallDist;
		if (tdata->ray->portal_hit)
		{
			if (!first_x)
				first_x = x;
			last_x = x;
		}
		ft_line_height(tdata->ray, tdata->data);
		ft_pre_render_line(tdata->data, tdata->ray, x, 0);
	}
	if (rec == 1)
		return ;
	ft_render_portal(tdata, first_x - 1, last_x + 1, rec + 1);
}

void	ft_render_portal(t_thread_data *tdata, int x, int end, int rec)
{
	int	first_x;
	int	last_x;

	first_x = 0;
	last_x = 0;
	if (rec >= 1000)
		return ;
	while (++x < end)
	{
		tdata->ray->portal_hit = false;
		tdata->ray->portal_see = false;
		ft_set_ray_loop(tdata->ray, x, tdata->data);
		ft_ray_dir(tdata->ray);
		ft_dda(tdata->ray, tdata->data, rec);
		ft_line_height(tdata->ray, tdata->data);
		ft_pre_render_line(tdata->data, tdata->ray, x, 1);
		if (tdata->ray->portal_hit)
		{
			if (!first_x)
				first_x = x;
			last_x = x;
		}
	}
	ft_render_portal(tdata, first_x - 1, last_x + 1, rec + 1);
}

void	*ft_thread_render(void *arg)
{
	t_thread_data	*tdata;
	int				x;

	tdata = (t_thread_data *)arg;
	x = tdata->start_x - 1;
	tdata->ray->drawEnd = 0;
	tdata->ray->drawStart = 0;
	tdata->ray->portal_hit = true;
	tdata->ray->portal_see = false;
	ft_first_render_loop(tdata, x, tdata->end_x, 0);
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
	ray->lineHeight = (int)(data->height / ray->perpWallDist);
	ray->drawStart = -(ray->lineHeight >> 1)
		+ (data->height >> 1) + data->player->angle_y;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = (ray->lineHeight >> 1)
		+ (data->height >> 1) + data->player->angle_y;
	if (ray->drawEnd >= data->height)
		ray->drawEnd = data->height - 1;
	if (ray->side == 0)
		ray->orien = (ray->stepX <= 0);
	else
		ray->orien = 2 + (ray->stepY <= 0);
}
