/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemies.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:35:41 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/07 16:37:34 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_render_enemy_loop(t_enemy_improv_render *edata, \
			t_enemy *enemy, t_data *data, int stripe)
{
	int	y;

	y = edata->drawStartY - 1;
	while (++y < edata->drawEndY)
	{
		edata->d = (y - data->player->angle_y) * 256
			- data->height * 128 + edata->spriteHeight * 128;
		edata->texY = ((edata->d * enemy->tex->y)
				/ edata->spriteHeight) / 256;
		if (edata->texY < 0)
			edata->texY = 0;
		if (edata->texY >= enemy->tex->y)
			edata->texY = enemy->tex->y - 1;
		edata->color = enemy->tex->addr[edata->texY
			* enemy->tex->x + edata->texX];
		if (edata->color != 0x000000)
		{
			data->zbuffer[stripe] = edata->transformY;
			data->img->addr[y * data->width + stripe] = edata->color;
		}
	}
}

void	ft_render_enemy_sprite(t_enemy_improv_render *edata, \
			t_enemy *enemy, t_data *data)
{
	int	stripe;

	stripe = edata->drawStartX - 1;
	while (++stripe < edata->drawEndX)
	{
		edata->texX = (int)(256 * (stripe - (-edata->spriteWidth / 2
						+ edata->spriteScreenX)) * enemy->tex->x
				/ edata->spriteWidth) / 256;
		if (edata->texX < 0)
			edata->texX = 0;
		if (edata->texX >= enemy->tex->x)
			edata->texX = enemy->tex->x - 1;
		if (edata->transformY > 0 && stripe > 0
			&& stripe < data->width && edata->transformY
			< data->zbuffer[stripe + 1])
			ft_render_enemy_loop(edata, enemy, data, stripe);
	}
}

void	ft_pre_render_enemy_sprite(t_data *data, t_ray *ray, t_enemy *enemy)
{
	t_enemy_improv_render	edata;

	ft_load_edata(data, ray, &edata);
	if (edata.drawStartY < 0)
		edata.drawStartY = 0;
	edata.drawEndY = edata.spriteHeight / 2
		+ data->height / 2 + data->player->angle_y;
	if (edata.drawEndY >= data->height)
		edata.drawEndY = data->height - 1;
	edata.spriteWidth = edata.spriteHeight;
	edata.drawStartX = -edata.spriteWidth / 2 + edata.spriteScreenX;
	if (edata.drawStartX < 0)
		edata.drawStartX = 0;
	edata.drawEndX = edata.spriteWidth / 2 + edata.spriteScreenX;
	if (edata.drawEndX >= data->width)
		edata.drawEndX = data->width - 1;
	ft_render_enemy_sprite(&edata, enemy, data);
}
