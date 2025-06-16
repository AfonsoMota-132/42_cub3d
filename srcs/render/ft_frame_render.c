/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:49:26 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 12:57:49 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_line_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx
				- ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty
				- ray->deltadisty);
	ray->lineheight = (int)(WIN_HEIGHT / ray->perpwalldist);
	ray->drawstart = -(ray->lineheight >> 1) + (WIN_HEIGHT >> 1);
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = (ray->lineheight >> 1) + (WIN_HEIGHT >> 1);
	if (ray->drawend >= WIN_HEIGHT)
		ray->drawend = WIN_HEIGHT - 1;
	ray->orien = get_wall_dir(ray->side, ray->stepx,
			ray->stepy);
}

void	ft_loop_door_handle(t_data *data, int x, bool erase)
{
	t_door	*tmp;

	tmp = data->head_door;
	while (tmp)
	{
		if (!tmp->seen && !erase
			&& x >= (WIN_WIDTH / 2) - 100
			&& x <= (WIN_WIDTH / 2) + 100
			&& data->ray->perpwalldist < 1.5
			&& tmp->x_pos == data->ray->mapx
			&& tmp->y_pos == data->ray->mapy)
			ft_door_handle_utils(tmp, data, true);
		else if (!tmp->seen && !erase)
			ft_door_handle_utils(tmp, data, false);
		if (erase)
			tmp->seen = false;
		tmp = tmp->next;
	}
}

void	ft_render_loop(t_data *data, int x, int door)
{
	ft_loop_door_handle(data, x, true);
	while (++x < WIN_WIDTH)
	{
		ft_set_ray_loop(data->ray, x);
		ft_ray_dir(data->ray);
		ft_dda(data, door);
		if (data->ray->hit == 2
			&& x >= (WIN_WIDTH / 2) - 100
			&& x <= (WIN_WIDTH / 2) + 100)
			ft_loop_door_handle(data, x, false);
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
		if (data->ray->sidedistx < data->ray->sidedisty)
		{
			data->ray->sidedistx += data->ray->deltadistx;
			data->ray->mapx += data->ray->stepx;
			data->ray->side = 0;
		}
		else
		{
			data->ray->sidedisty += data->ray->deltadisty;
			data->ray->mapy += data->ray->stepy;
			data->ray->side = 1;
		}
		if (door && data->map->map[data->ray->mapx][data->ray->mapy] == 'H')
			data->ray->hit = 2;
		else if (data->map->map[data->ray->mapx][data->ray->mapy] == '1')
			data->ray->hit = 1;
	}
}
