/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:50:51 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:16 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_render_minimap_sq(t_data *data, int xs, int ys, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= (data->minimap_height / 20))
	{
		x = -1;
		while (++x <= (data->minimap_width / 20))
		{
			data->img_minimap->addr[(int)((y
						+ (ys * data->minimap_height / 20))
					* data->minimap_width + x
					+ (xs * data->minimap_width / 20))] = color;
		}
	}
}

void	ft_pre_flip_minimap(t_minimap *mp, t_data *data)
{
	mp->angle = 0;
	mp->height = data->minimap_height;
	mp->width = data->minimap_width;
	mp->rad = mp->angle * M_PI / 180.0;
	mp->cos_a = cos(mp->rad);
	mp->sin_a = -sin(mp->rad);
	mp->cx = mp->width / 2;
	mp->cy = mp->height / 2;
}

void	ft_flip_minimap(t_data *data)
{
	t_minimap	mp;
	int			y;
	int			x;

	ft_pre_flip_minimap(&mp, data);
	y = -1;
	while (++y < mp.height)
	{
		x = -1;
		while (++x < mp.width)
		{
			mp.dx = x - mp.cx;
			mp.dy = y - mp.cy;
			mp.src_x = (int)(mp.cos_a * mp.dx + mp.sin_a * mp.dy) + mp.cx;
			mp.src_y = (int)(-mp.sin_a * mp.dx + mp.cos_a * mp.dy) + mp.cy;
			if (mp.src_x >= 0 && mp.src_x < mp.width
				&& mp.src_y >= 0 && mp.src_y < mp.height)
				data->img->addr[y * (WIN_WIDTH) + x]
					= data->img_minimap->addr[mp.src_y * mp.width + mp.src_x];
			else
				data->img->addr[y * (WIN_WIDTH) + x] = 0x00000000;
		}
	}
}

void	ft_render_minimap_utils(t_data *data, t_minimap_utils mp)
{
	if (data->map->map[mp.pos_x][mp.pos_y] == '0'
		|| data->map->map[mp.pos_x][mp.pos_y] == 'X'
		|| data->map->map[mp.pos_x][mp.pos_y] == 'P')
		ft_render_minimap_sq(data, mp.y, mp.x, 0xFFFFFF);
	else if (data->map->map[mp.pos_x][mp.pos_y] == '1')
		ft_render_minimap_sq(data, mp.y, mp.x, 0x000000);
	else if (data->map->map[mp.pos_x][mp.pos_y] == 'H')
		ft_render_minimap_sq(data, mp.y, mp.x, 0x0000FF);
	if ((mp.pos_x == (int) data->player->x_pos
			&& mp.pos_y == (int) data->player->y_pos))
		ft_render_minimap_sq(data, mp.y, mp.x, 0xFF0000);
}

void	ft_render_minimap(t_data *data)
{
	t_minimap_utils	mp;

	mp.pos_y = (data->player->y_pos) - 10;
	mp.y = -1;
	while (++mp.y < 20)
	{
		mp.x = -1;
		mp.pos_x = (data->player->x_pos) - 10;
		while (++mp.x < 20)
		{
			if (mp.pos_x > 0 && mp.pos_y > 0
				&& mp.pos_x < data->map->max_height
				&& mp.pos_y < (int) ft_strlen(data->map->map[mp.pos_x]))
				ft_render_minimap_utils(data, mp);
			else
				ft_render_minimap_sq(data, mp.y, mp.x, 0x000000);
			mp.pos_x++;
		}
		mp.pos_y++;
	}
	ft_flip_minimap(data);
}
