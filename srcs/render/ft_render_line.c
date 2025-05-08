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
	int	color;

	while (++y <= WIN_HEIGHT)
	{
		if (y < line.drawStart)
			line.addr[y * line.img_sl + x] = line.hex_ceil;
		else if (y > line.drawEnd)
			line.addr[y * line.img_sl + x] = line.hex_floor;
		else
		{
			line.texPos += line.step;
			color = line.tex_addr[((int)line.texPos
					& (line.text_y)) * (line.tex_sl) + line.texX];
			if (color)
				line.addr[y * line.img_sl + x] = color; 
		}
	}
}

void	ft_ray_render_line(t_ray *ray, t_data *data)
{
	ray->wallX = (ray->posY + ray->perpWallDist
		* ray->rayDirY) * (ray->side == 0)
	+ (ray->posX + ray->perpWallDist * ray->rayDirX)
	* (ray->side != 0);
	ray->wallX -= floor(ray->wallX);
	ray->texX = (int)(ray->wallX * (double)data->texture_wall->x);
	ray->texX = ray->texX + ((ray->side == 0
				&& ray->rayDirX > 0) || (ray->side == 1
				&& ray->rayDirY < 0)) * (data->texture_wall->x
			- ray->texX - ray->texX - 1);
}

void	ft_pre_render_line(t_data *data, t_ray *ray, int x, int y)
{
	t_line_improv_render	line;

	data->texture_wall = data->tex_north;
	if (ray->orien == 1)
		data->texture_wall = data->tex_south;
	if (ray->orien == 2)
		data->texture_wall = data->tex_west;
	if (ray->orien == 3)
		data->texture_wall = data->tex_east;
	ft_ray_render_line(ray, data);
	line.addr = data->img->addr;
	line.step = 1.0 * data->texture_wall->y / ray->lineHeight;
	line.texPos = (ray->drawStart - data->player->angle_y - (WIN_HEIGHT >> 1)
			+ (ray->lineHeight >> 1)) * line.step;
	line.hex_ceil = data->hex_ceiling;
	line.hex_floor = data->hex_floor;
	line.img_sl = (data->img->size_line >> 2);
	line.tex_sl = data->texture_wall->size_line >> 2;
	line.text_y = data->texture_wall->y - 1;
	line.tex_addr = data->texture_wall->addr;
	line.drawEnd = ray->drawEnd;
	line.drawStart = ray->drawStart;
	line.texX = ray->texX;
	ft_render_line(x, y, line);
}
