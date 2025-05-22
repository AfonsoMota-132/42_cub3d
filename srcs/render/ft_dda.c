/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:20:35 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:20:55 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_dda(t_ray *ray, t_data *data, char door)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->rayPosX += ray->stepX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->rayPosY += ray->stepY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (data->bigmap[ray->mapX][ray->mapY] == '1')
			ray->hit = 1;
		if (door >= 0 && data->bigmap[ray->mapX][ray->mapY] == door)
			ray->hit = 2;
	}
	if (ray->hit == 2)
	{
		int	i = -1;
		while (data->door[++i])
		{
			if (((int) (ray->mapX / data->scale) == (int) data->door[i]->x_pos)
				&& (((int) (ray->mapY / data->scale) == (int) data->door[i]->y_pos)))
				ray->door = data->door[i];
		}
	}
	ray->posX /= data->scale;
	ray->posY /= data->scale;
}

char	ft_dda_shoot(t_ray *ray, t_data *data)
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
		if (enemy >= 'A' && enemy <= 'K')
			return (enemy);
		if (enemy == '1')
			return ('1');
	}
	return (0);
}

void	ft_dda_enemies_utils(t_ray *ray, t_data *data)
{
	if (data->map[ray->mapX][ray->mapY] == 'P')
		ray->hit = 3;
	if (data->map[ray->mapX][ray->mapY] == '1')
		ray->hit = 1;
}

void	ft_dda_enemies(t_ray *ray, t_data *data)
{
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
		ft_dda_enemies_utils(ray, data);
	}
}
