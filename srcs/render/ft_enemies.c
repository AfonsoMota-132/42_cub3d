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

#include "../../incs/cub3d.h"

void	ft_dda_enemy(t_ray *ray, t_data *data, char detect)
{
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
		enemy = data->map[ray->mapX][ray->mapY];
		if (enemy == detect)
			ray->hit = 2;
		if (enemy == '1')
			ray->hit = 1;
	}
	for (int i = 0; data->enemy_arr[i]; i++)
	{
		if (data->enemy_arr[i]->map == enemy)
			data->enemy = data->enemy_arr[i];
	}
}
