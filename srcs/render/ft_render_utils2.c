/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:16:26 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:17:28 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

int	ft_pixel_darken(int color, double factor)
{
	int	ret;
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	ret = (r << 16) | (g << 8) | b;
	return (ret);
}

void	ft_frame_render_pause_utils(t_data *data)
{
	int				x;
	t_frame_pause	fdata;
	int				y;

	x = -1;
	while (++x < (0.2 * data->width))
	{
		y = -1;
		while (++y < (0.4 * data->height))
		{
			fdata.texX = (x * 106) / (0.2 * data->width);
			fdata.texY = (y * 122) / (0.4 * data->height);
			fdata.color = data->tex_pause->addr[fdata.texY * 106 + fdata.texX];
			if (fdata.color != 0x000000)
				data->img_pause->addr[(int)(y * data->width
						+ ((data->height * 0.3) * data->width) \
					+ x + ((0.4 * data->width)))] = fdata.color;
		}
	}
}
