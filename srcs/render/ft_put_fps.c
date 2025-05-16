/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:17:34 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:18:05 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_render_put_fps(t_img *img, t_img *nbr, int x_offset, t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = -1;
	while (++x < nbr->x)
	{
		y = -1;
		while (++y < nbr->y)
		{
			color = nbr->addr[y * 32 + x];
			if (color != 0x000000)
				img->addr[y * data->width + x + x_offset] = color;
		}
	}
}

void	ft_put_fps_utils(t_data *data, char *str, int i, int offset)
{
	if (str[i] == '0')
		ft_render_put_fps(data->img, data->nbrs->nbr_0, offset, data);
	else if (str[i] == '1')
		ft_render_put_fps(data->img, data->nbrs->nbr_1, offset, data);
	else if (str[i] == '2')
		ft_render_put_fps(data->img, data->nbrs->nbr_2, offset, data);
	else if (str[i] == '3')
		ft_render_put_fps(data->img, data->nbrs->nbr_3, offset, data);
	else if (str[i] == '4')
		ft_render_put_fps(data->img, data->nbrs->nbr_4, offset, data);
	else if (str[i] == '5')
		ft_render_put_fps(data->img, data->nbrs->nbr_5, offset, data);
	else if (str[i] == '6')
		ft_render_put_fps(data->img, data->nbrs->nbr_6, offset, data);
	else if (str[i] == '7')
		ft_render_put_fps(data->img, data->nbrs->nbr_7, offset, data);
	else if (str[i] == '8')
		ft_render_put_fps(data->img, data->nbrs->nbr_8, offset, data);
	else if (str[i] == '9')
		ft_render_put_fps(data->img, data->nbrs->nbr_9, offset, data);
}

void	ft_put_fps(t_data *data)
{
	char	*str;
	int		offset;
	int		i;

	str = ft_itoa((int) data->fps);
	i = -1;
	offset = 0;
	while (str[++i])
	{
		ft_put_fps_utils(data, str, i, offset);
		offset += 16;
	}
	free(str);
}
