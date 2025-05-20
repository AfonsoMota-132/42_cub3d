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

void	ft_dda_utils(t_ray *ray, t_data *data, int x, int rec)
{
	if (data->map[ray->mapX][ray->mapY] == '1')
		ray->hit = 1;
	if ((data->map[ray->mapX][ray->mapY] == 'R'
		|| data->map[ray->mapX][ray->mapY] == 'L')
		&& ray->count < rec)
	{
		if (ray->side == 0)
			ray->orien = (ray->stepX <= 0);
		else
			ray->orien = 2 + (ray->stepY <= 0);
		if (data->map[ray->mapX][ray->mapY] == 'R'
			&& ray->orien == data->portalR->orien)
		{

ray->posX = 7.5;
ray->posY = 2.5;

double angle = M_PI / 2.0;
double oldDirX = ray->dirX;
ray->dirX = cos(angle) * ray->dirX - sin(angle) * ray->dirY;
ray->dirY = sin(angle) * oldDirX + cos(angle) * ray->dirY;

double oldPlaneX = ray->planeX;
ray->planeX = ray->dirY * 0.66; 
ray->planeY = -ray->dirX * 0.66;

ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;

ray->mapX = (int)ray->posX;
ray->mapY = (int)ray->posY;
ray->deltaDistX = fabs(1.0 / (ray->rayDirX + (ray->rayDirX == 0) * 1e-30));
ray->deltaDistY = fabs(1.0 / (ray->rayDirY + (ray->rayDirY == 0) * 1e-30));
ft_ray_dir(ray);
			ray->count++;
			ray->portal_see = true;
		}
		else
			ray->hit = 1;
	}
	else if (data->map[ray->mapX][ray->mapY] == 'R'
		|| data->map[ray->mapX][ray->mapY] == 'L')
		ray->hit = 2;
}

void	ft_dda(t_ray *ray, t_data *data, int x,int rec)
{
	double	posX = ray->posX;
	double	posY = ray->posY;
	double	deltaDistX = ray->deltaDistX;
	double	deltaDistY = ray->deltaDistX;
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
		ft_dda_utils(ray, data, x,rec);
		if (data->map[ray->mapX][ray->mapY] == 'R'
			&& ray->count == rec)
			ray->portal_hit = true;
	}
	printf("sideDistX %f\t sideDistY %f\n", ray->sideDistX, ray->sideDistY);
	ray->posX = posX;
	ray->posY = posY;
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
