/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_portal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:54:01 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:54:49 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_pre_render_loop_portal(t_ray *ray, t_portal *portal)
{
	ray->dirX = portal->x_look;
	ray->dirY = portal->y_look;
	ray->posX = portal->x_pos;
	ray->posY = portal->y_pos;
	ray->planeX = ray->dirY * 0.66;
	ray->planeY = -ray->dirX * 0.66;
}

void	ft_set_ray_loop_portal(t_ray *ray, int x, t_data *data)
{
	ray->cameraX = (2 * x / (double)data->width - 1)
		* ((double)data->width / data->height);
	ray->rayDirX = ray->dirX + ray->planeX
		* ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY
		* ray->cameraX;
	ray->mapX = (int) ray->posX;
	ray->mapY = (int) ray->posY;
	ray->hit = 0;
	ray->deltaDistX = fabs(1 / (ray->rayDirX
				+ (ray->rayDirX == 0) * 1e-30));
	ray->deltaDistY = fabs(1 / (ray->rayDirY
				+ (ray->rayDirY == 0) * 1e-30));
}

void	ft_render_line_portal(int x, t_line_improv_render *line, \
			t_data *data, t_ray *ray)
{
	int	color;
	int	color2;
	int	y;

	y = -1;
	while (++y <= data->height)
	{
		color2 = line->addr[y * line->img_sl + x];
		if (y >= ray->drawStart && y <= line->drawEnd)
			line->texPos += line->step;
		if (color2 == 0xFFFFFF)
		{
			if (y < ray->drawStart)
				line->addr[y * line->img_sl + x] = line->hex_ceil;
			else if (y > line->drawEnd)
				line->addr[y * line->img_sl + x] = line->hex_floor;
			else
			{
				color = line->tex_addr[((int)line->texPos
						& (line->text_y)) * (line->tex_sl) + line->texX];
				if (color)
					line->addr[y * line->img_sl + x] = color;
			}
		}
	}
}
