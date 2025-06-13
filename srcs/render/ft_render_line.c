/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:29:55 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/06 09:29:57 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

double	ft_add_angle(double angle, double delta)
{
	angle += delta;
	if (angle >= 360.0)
		angle -= 360.0;
	else if (angle < 0.0)
		angle += 360.0;
	return (angle);
}

void	ft_render_line(int x, int y, t_line_improv_render line)
{
	while (++y <= WIN_HEIGHT)
	{
		if (y < line.drawStart)
			line.addr[y * line.img_sl + x] = line.hex_ceil;
		else if (y > line.drawEnd)
			line.addr[y * line.img_sl + x] = line.hex_floor;
		else
		{
			line.texPos += line.step;
			line.addr[y * line.img_sl + x] = line.tex_addr[((int)line.texPos
					& (line.text_y)) * (line.tex_sl) + line.texX];
		}
	}
}

void	ft_ray_render_line(t_data *data)
{
	data->ray->wallX = (data->ray->posY + data->ray->perpWallDist
			* data->ray->rayDirY) * (data->ray->side == 0)
		+ (data->ray->posX + data->ray->perpWallDist * data->ray->rayDirX)
		* (data->ray->side != 0);
	data->ray->wallX -= floor(data->ray->wallX);
	data->ray->texX = (int)(data->ray->wallX * (double)data->texture_wall->x);
	data->ray->texX = data->ray->texX + ((data->ray->side == 0
				&& data->ray->rayDirX > 0) || (data->ray->side == 1
				&& data->ray->rayDirY < 0)) * (data->texture_wall->x
			- data->ray->texX - data->ray->texX - 1);
}

void	ft_pre_render_line(t_data *data, int x, int y)
{
	t_line_improv_render	line;

	data->texture_wall = data->tex_north;
	if (data->ray->orien == 1)
		data->texture_wall = data->tex_south;
	if (data->ray->orien == 2)
		data->texture_wall = data->tex_west;
	if (data->ray->orien == 3)
		data->texture_wall = data->tex_east;
	ft_ray_render_line(data);
	line.addr = data->img->addr;
	line.step = 1.0 * data->texture_wall->y / data->ray->lineHeight;
	line.texPos = (data->ray->drawStart - (WIN_HEIGHT >> 1)
			+ (data->ray->lineHeight >> 1)) * line.step;
	line.hex_ceil = data->hex_ceiling;
	line.hex_floor = data->hex_floor;
	line.img_sl = (data->img->size_line >> 2);
	line.tex_sl = data->texture_wall->size_line >> 2;
	line.text_y = data->texture_wall->y - 1;
	line.tex_addr = data->texture_wall->addr;
	line.drawEnd = data->ray->drawEnd;
	line.drawStart = data->ray->drawStart;
	line.texX = data->ray->texX;
	ft_render_line(x, y, line);
}
