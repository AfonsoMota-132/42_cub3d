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

void	ft_dda_utils(t_ray *ray, t_data *data, int rec)
{
	if (data->map[ray->mapX][ray->mapY] == '1')
		ray->hit = 1;
	if (data->map[ray->mapX][ray->mapY] == 'R'
		&& ray->count < rec)
	{
		if (ray->side == 0)
			ray->orien = (ray->stepX <= 0);
		else
			ray->orien = 2 + (ray->stepY <= 0);
		if (ray->orien == 2)
		{
			ray->mapX = 2;
			ray->mapY = 1;
			ray->count++;
			ray->portal_see = true;
		}
		else
			ray->hit = 1;
	}
	else if (data->map[ray->mapX][ray->mapY] == 'R')
		ray->hit = 2;
}

void	ft_dda(t_ray *ray, t_data *data, int rec)
{
	ray->count = 0;
	ray->portal_see = false;
	ray->portal_hit = false;
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
		ft_dda_utils(ray, data, rec);
		if (data->map[ray->mapX][ray->mapY] == 'R'
			&& ray->count == rec)
			ray->portal_hit = true;
	}
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
	if (!ray->portal_hit && data->map[ray->mapX][ray->mapY] == 'R')
	{
		if (ray->side == 0)
			ray->orien = (ray->stepX <= 0);
		else
			ray->orien = 2 + (ray->stepY <= 0);
		if (ray->orien == 2)
		{
			ray->mapX = 6;
			ray->mapY = 1;
			if (!data->see_portal)
				data->see_portal = true;
		}
		else
			ray->hit = 1;
	}
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
