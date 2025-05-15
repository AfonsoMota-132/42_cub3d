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

void	ft_render_line(int x, t_line_improv_render *line, t_data *data, t_ray *ray)
{
	int	color;
	int	y;

	y = -1;
	while (++y <= data->height)
	{
		if (y < ray->drawStart)
			line->addr[y * line->img_sl + x] = line->hex_ceil;
		else if (y > line->drawEnd)
			line->addr[y * line->img_sl + x] = line->hex_floor;
		else
		{
			line->texPos += line->step;
			color = line->tex_addr[((int)line->texPos
					& (line->text_y)) * (line->tex_sl) + line->texX];
			if (color)
				line->addr[y * line->img_sl + x] = color; 
		}
		if (ray->count == 1)
		{
			int	color2 = line->addr[y * line->img_sl + x];
			float	factor	= 0.45;
			int r = ((color2 >> 16) & 0xFF) * factor;
			int g = ((color2 >> 8) & 0xFF) * factor;
			int b = (color2 & 0xFF) * factor;
			color2 = (r << 16) | (g << 8) | b;
			line->addr[y * data->width + x] = color2;
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

void	ft_pre_render_loop_portal(t_ray *ray, t_portal *portal)
{
	ray->dirX = portal->x_look;
	ray->dirY = portal->y_look;
	ray->posX = portal->x_pos;
	ray->posY = portal->y_pos;
	ray->planeX = ray->dirY * 0.66;
	ray->planeY = -ray->dirX * 0.66;
}

void	ft_render_line_portal(int x, t_line_improv_render *line, t_data *data, t_ray *ray)
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
			color2 = line->addr[y * line->img_sl + x];
			float	factor	= 0.45;
			int r = ((color2 >> 16) & 0xFF) * factor;
			int g = ((color2 >> 8) & 0xFF) * factor;
			int b = (color2 & 0xFF) * factor;
			color2 = (r << 16) | (g << 8) | b;
			line->addr[y * data->width + x] = color2;
		}
	}
}

void	ft_pre_render_line(t_data *data, t_ray *ray, int x)
{
	t_line_improv_render	line;

	data->texture_wall = data->tex_north;
	if (ray->orien == 1)
		data->texture_wall = data->tex_south;
	if (ray->orien == 2)
		data->texture_wall = data->tex_west;
	if (ray->orien == 3)
		data->texture_wall = data->tex_east;
	if (ray->hit == 2)
		data->texture_wall = data->tex_pl;
	ft_ray_render_line(ray, data);
	line.addr = data->img->addr;
	line.height = data->height;
	line.width = data->width;
	line.step = 1.0 * data->texture_wall->y / ray->lineHeight;
	line.texPos = (ray->drawStart - data->player->angle_y - (line.height >> 1)
			+ (ray->lineHeight >> 1)) * line.step;
	line.hex_ceil = data->hex_ceiling;
	line.hex_floor = data->hex_floor;
	line.img_sl = (data->img->size_line >> 2);
	line.tex_sl = data->texture_wall->size_line >> 2;
	line.text_y = data->texture_wall->y - 1;
	line.tex_addr = data->texture_wall->addr;
	line.drawEnd = 0;
	line.drawStart = 0;
	line.drawEnd = ray->drawEnd;
	line.drawStart = ray->drawStart;
	line.texX = ray->texX;
	line.portal_hit = ray->portal_see;
	line.count = ray->count;
	if (!line.portal_hit)
		ft_render_line(x, &line, data, ray);
	else
		ft_render_line_portal(x, &line, data, ray);
}
