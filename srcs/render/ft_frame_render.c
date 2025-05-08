/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:49:26 by afogonca          #+#    #+#             */
/*   Updated: 2025/04/26 09:54:48 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_line_height(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX
				- ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY
				- ray->deltaDistY);
	ray->lineHeight = (int)(WIN_HEIGHT / ray->perpWallDist);
	ray->drawStart = -(ray->lineHeight >> 1) + (WIN_HEIGHT >> 1) + data->player->angle_y;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = (ray->lineHeight >> 1) + (WIN_HEIGHT >> 1) + data->player->angle_y;
	if (ray->drawEnd >= WIN_HEIGHT)
		ray->drawEnd = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->orien = (ray->stepX <= 0);
	else
		ray->orien = 2 + (ray->stepY <= 0);
}

void *thread_render(void *arg)
{
    t_thread_data *tdata = (t_thread_data *)arg;
    int x = tdata->start_x - 1;

    while (++x < tdata->end_x)
    {
        ft_set_ray_loop(tdata->ray, x);
        ft_ray_dir(tdata->ray);
        ft_dda(tdata->ray, tdata->data);
        ft_line_height(tdata->ray, tdata->data);
        ft_pre_render_line(tdata->data, tdata->ray, x, -1);
    }
    return (NULL);
}

void	ft_line_height_enemy(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX
				- ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY
				- ray->deltaDistY);
	if (ray->hit == 2)
		ray->perpWallDist += 0.5; // Increase this (e.g., 0.5) if still too close
	ray->lineHeight = (int)(WIN_HEIGHT / ray->perpWallDist);
	if (ray->hit == 2)
		ray->lineHeight *= 0.6; // Try 0.6 for smaller enemies
	ray->drawStart = -(ray->lineHeight >> 1) + (WIN_HEIGHT >> 1) + data->player->angle_y;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = (ray->lineHeight >> 1) + (WIN_HEIGHT >> 1) + data->player->angle_y;
	if (ray->drawEnd >= WIN_HEIGHT)
		ray->drawEnd = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->orien = (ray->stepX <= 0);
	else
		ray->orien = 2 + (ray->stepY <= 0);
}
void	ft_render_line_enemy(int x, int y, t_line_improv_render line)
{
	int	color;

	y = line.drawStart;
	while (++y <= line.drawEnd)
	{
		line.texPos += line.step;
		color = line.tex_addr[((int)line.texPos
			& (line.text_y)) * (line.tex_sl) + line.texX];
		if (color)
			line.addr[y * line.img_sl + x] = color; 
	}
}

void	ft_ray_render_line_enemy(t_ray *ray, t_data *data)
{
	ray->wallX = (ray->posY + ray->perpWallDist
		* ray->rayDirY) * (ray->side == 0)
	+ (ray->posX + ray->perpWallDist * ray->rayDirX)
	* (ray->side != 0);
	ray->wallX -= floor(ray->wallX);
	ray->texX = (int)(ray->wallX * (double)data->texture_wall->x);
	ray->texX = ray->texX + ((ray->side == 0
				&& ray->rayDirX > 0) || (ray->side == 1
				&& ray->rayDirY < 0)) * (data->texture_wall->x
			- ray->texX - ray->texX - 1);
}

void	ft_pre_render_line_enemy(t_data *data, t_ray *ray, int x, int y)
{
	t_line_improv_render	line;

	data->texture_wall = data->tex_enemy;
	ft_ray_render_line_enemy(ray, data);
	line.addr = data->img->addr;
	line.step = 1.0 * data->texture_wall->y / ray->lineHeight;
	line.texPos = (ray->drawStart - data->player->angle_y - (WIN_HEIGHT >> 1)
			+ (ray->lineHeight >> 1)) * line.step;
	line.hex_ceil = data->hex_ceiling;
	line.hex_floor = data->hex_floor;
	line.img_sl = (data->img->size_line >> 2);
	line.tex_sl = data->texture_wall->size_line >> 2;
	line.text_y = data->texture_wall->y - 1;
	line.tex_addr = data->texture_wall->addr;
	line.drawEnd = ray->drawEnd;
	line.drawStart = ray->drawStart;
	line.texX = ray->texX;
	ft_render_line_enemy(x, y, line);
}

void ft_render_enemy_sprite(t_data *data, t_ray *ray, double enemyX, double enemyY)
{

double dirX = data->player->x_look;
double dirY = data->player->y_look;
double planeX = ray->planeX;
double planeY = ray->planeY;
    double spriteX = enemyX - data->ray->posX;
    double spriteY = enemyY - data->ray->posY;

double invDet = 1.0 / (planeX * dirY - dirX * planeY);

// Correct transform
double transformX = invDet * (dirY * spriteX - dirX * spriteY);
double transformY = invDet * (-planeY * spriteX + planeX * spriteY);
// int spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + transformX / transformY));
	int spriteScreenX = (int)((WIN_WIDTH / 2) + (transformX / transformY) * (WIN_WIDTH / 4));
    int spriteHeight = abs((int)(WIN_HEIGHT / transformY));
    int drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2 + data->player->angle_y;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2 + data->player->angle_y;
    if (drawEndY >= WIN_HEIGHT) drawEndY = WIN_HEIGHT - 1;
    int spriteWidth = spriteHeight;
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= WIN_WIDTH) drawEndX = WIN_WIDTH - 1;
    for (int stripe = drawStartX; stripe < drawEndX; stripe++)
    {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->tex_enemy->x / spriteWidth) / 256;
        if (texX < 0) texX = 0;
        if (texX >= data->tex_enemy->x) texX = data->tex_enemy->x - 1;

        if (transformY > 0 && stripe > 0 && stripe < WIN_WIDTH)
        {
            for (int y = drawStartY; y < drawEndY; y++)
            {
                int d = (y - data->player->angle_y) * 256 - WIN_HEIGHT * 128 + spriteHeight * 128;
                int texY = ((d * data->tex_enemy->y) / spriteHeight) / 256;
                if (texY < 0) texY = 0;
                if (texY >= data->tex_enemy->y) texY = data->tex_enemy->y - 1;

                int color = data->tex_enemy->addr[texY * data->tex_enemy->x + texX];

                if (color != 0x000000)
                    data->img->addr[y * WIN_WIDTH + stripe] = color;
            }
        }
    }
}

int	ft_frame_render(t_data *data)
{
	int	i;

	while (ft_get_time_in_ms() <= data->time_frame)
		;
	data->time_frame = ft_get_time_in_ms() + 16.6;
	data->fps = 1000 / (ft_get_time_in_ms() - data->old_frame);
	data->old_frame = ft_get_time_in_ms();
	ft_player_mov(data);
	ft_pre_render_loop(data->ray, data->player);
	i = -1;
	while (++i < data->nbr_threads)
	{
		ft_pre_render_loop(data->tdata[i].ray, data->player);
		pthread_create(&data->thread[i], NULL, thread_render, &data->tdata[i]);
	}
	i = -1;
	while (++i < data->nbr_threads)
		pthread_join(data->thread[i], NULL);
	
	int x = - 1;
	
	while (++x < WIN_WIDTH)
	{
		ft_pre_render_loop(data->ray, data->player);
		ft_set_ray_loop(data->ray, x);
		ft_ray_dir(data->ray);
		ft_dda_enemy(data->ray, data);
		if (data->ray->hit == 2)
		{
			ft_render_enemy_sprite(data, data->ray, 2.5, 3.5);
			break ;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

void	ft_dda(t_ray *ray, t_data *data)
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
		if (data->map[ray->mapX][ray->mapY] == '1')
			ray->hit = 1;
	}
}
