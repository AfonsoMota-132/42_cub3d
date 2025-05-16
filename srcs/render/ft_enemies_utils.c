/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemies_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:32:39 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:35:35 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

char	ft_dda_enemy2(t_ray *ray, t_data *data, char detect)
{
	char	enemy;

	enemy = data->map[ray->mapX][ray->mapY];
	if (enemy == detect)
		ray->hit = 2;
	if (enemy == '1')
		ray->hit = 1;
	if (data->map[ray->mapX][ray->mapY] == 'R')
	{
		ray->mapX = data->portal->x_pos;
		ray->mapY = data->portal->y_pos;
		data->see_portal = true;
	}
	return (enemy);
}

void	ft_load_edata(t_data *data, t_ray *ray, \
				t_enemy_improv_render *edata)
{
	edata->dirX = data->player->x_look;
	edata->dirY = data->player->y_look;
	edata->planeX = ray->planeX;
	edata->planeY = ray->planeY;
	edata->spriteX = data->enemy->data->x_pos - data->ray->posX;
	edata->spriteY = data->enemy->data->y_pos - data->ray->posY;
	edata->invDet = 1.0 / (edata->planeX * edata->dirY
			- edata->dirX * edata->planeY);
	edata->transformX = edata->invDet * (edata->dirY
			* edata->spriteX - edata->dirX * edata->spriteY);
	edata->transformY = edata->invDet * (-edata->planeY
			* edata->spriteX + edata->planeX * edata->spriteY);
	edata->spriteScreenX = (int)((data->width / 2)
			+ (edata->transformX / edata->transformY) * (data->width / 4));
	edata->spriteHeight = abs((int)(data->height / edata->transformY));
	edata->drawStartY = -edata->spriteHeight / 2
		+ data->height / 2 + data->player->angle_y;
}

void	ft_dda_enemy(t_ray *ray, t_data *data, char detect)
{
	int		i;
	char	enemy;

	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		enemy = ft_dda_enemy2(ray, data, detect);
	}
	i = -1;
	while (data->enemy_arr[++i])
	{
		if (data->enemy_arr[i]->map == enemy)
			data->enemy = data->enemy_arr[i];
	}
}

void	ft_raycasting_enemies_utils2(t_data *data, t_enemy *enemy, \
				int x, int first_x)
{
	enemy->ray->sideDistX = fabs(data->player->y_pos - enemy->data->x_pos);
	enemy->ray->sideDistX = fabs(data->player->y_pos - enemy->data->y_pos);
	x = (x + first_x) / 2;
	if (x > (data->width / 2) && first_x != -1)
	{
		enemy->data->angle = ft_add_angle(enemy->data->angle, +2.5);
		enemy->data->y_look = cos(enemy->data->angle * M_PI / 180.0);
		enemy->data->x_look = sin(enemy->data->angle * M_PI / 180.0);
	}
	if (x < (data->width / 2) && first_x != -1)
	{
		enemy->data->angle = ft_add_angle(enemy->data->angle, -2.5);
		enemy->data->y_look = cos(enemy->data->angle * M_PI / 180.0);
		enemy->data->x_look = sin(enemy->data->angle * M_PI / 180.0);
	}
}

double	ft_calc_dist_sq(t_data *data, t_enemy *enemy)
{
	return (((enemy->data->x_pos - data->player->x_pos) * (enemy->data->x_pos
				- data->player->x_pos)) + ((enemy->data->y_pos
				- data->player->y_pos) * (enemy->data->y_pos
				- data->player->y_pos)));
}
