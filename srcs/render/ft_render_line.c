/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:29:55 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 14:13:15 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_render_line(int x, int y, t_line_improv_render line)
{
	while (++y <= WIN_HEIGHT)
	{
		if (y < line.drawstart)
			line.addr[y * line.img_sl + x] = line.hex_ceil;
		else if (y > line.drawend)
			line.addr[y * line.img_sl + x] = line.hex_floor;
		else
		{
			line.texpos += line.step;
			if (line.hit != 2)
				line.addr[y * line.img_sl + x] = line.tex_addr[((int)line.texpos
						& (line.text_y)) * (line.tex_sl) + line.texx];
		}
	}
}

void	ft_render_line_door(int x, t_line_improv_render *line, \
				int colorDodge)
{
	int	color;
	int	y;

	y = -1;
	while (++y <= WIN_HEIGHT
		&& ((int) line->texpos & line->text_y) + (int)(line->door * 64) < 64)
	{
		if (y >= line->drawstart && y <= line->drawend)
		{
			line->texpos += line->step;
			color = line->tex_addr[(((((int)line->texpos
								& (line->text_y)) + (int)(line->door * 64))
						* (line->tex_sl)) + line->texx)];
			if (color && (colorDodge < 0
					|| (colorDodge >= 0 && color != colorDodge)))
				line->addr[y * line->img_sl + x] = color;
		}
	}
}

void	ft_ray_render_line(t_data *data)
{
	data->ray->wallx = (data->ray->posy + data->ray->perpwalldist
			* data->ray->raydiry) * (data->ray->side == 0)
		+ (data->ray->posx + data->ray->perpwalldist * data->ray->raydirx)
		* (data->ray->side != 0);
	data->ray->wallx -= floor(data->ray->wallx);
	data->ray->texx = (int)(data->ray->wallx * (double)data->texture_wall->x);
	data->ray->texx = data->ray->texx + ((data->ray->side == 0
				&& data->ray->raydirx > 0) || (data->ray->side == 1
				&& data->ray->raydiry < 0)) * (data->texture_wall->x
			- data->ray->texx - data->ray->texx - 1);
}

void	ft_init_line(t_data *data, t_line_improv_render *line)
{
	line->addr = data->img->addr;
	line->step = 1.0 * data->texture_wall->y / data->ray->lineheight;
	line->texpos = (data->ray->drawstart - (WIN_HEIGHT >> 1)
			+ (data->ray->lineheight >> 1)) * line->step;
	line->hex_ceil = data->hex_ceiling;
	line->hex_floor = data->hex_floor;
	line->img_sl = (data->img->size_line >> 2);
	line->tex_sl = data->texture_wall->size_line >> 2;
	line->text_y = data->texture_wall->y - 1;
	line->tex_addr = data->texture_wall->addr;
	line->drawend = data->ray->drawend;
	line->drawstart = data->ray->drawstart;
	line->texx = data->ray->texx;
	line->door = 1;
	line->hit = data->ray->hit;
	if (data->ray->hit == 2)
		line->door = ft_door_state(data, data->ray->mapx, data->ray->mapy);
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
	if (data->ray->hit == 2)
		data->texture_wall = data->tex_east;
	ft_ray_render_line(data);
	ft_init_line(data, &line);
	if (data->ray->hit == 2)
		ft_render_line_door(x, &line, 0x000000);
	else
		ft_render_line(x, y, line);
}
