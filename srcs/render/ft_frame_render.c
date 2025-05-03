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

#include "../../incs/cub3d.h"
double ft_add_angle(double angle, double delta)
{
    angle += delta;
    if (angle >= 360.0)
        angle -= 360.0;
    else if (angle < 0.0)
        angle += 360.0;
    return angle;
}

void	ft_player_rot(t_data *data)
{
	if (data->mov->lookl)
	{
		data->player->angle = ft_add_angle(data->player->angle, -2.5);
		data->player->y_look = cos(data->player->angle * M_PI / 180.0);
		data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	}
	if (data->mov->lookr)
	{
		data->player->angle = ft_add_angle(data->player->angle, 2.5);
		data->player->y_look = cos(data->player->angle * M_PI / 180.0);
		data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	}
}
void	ft_player_mov(t_data *data)
{
	ft_player_rot(data);
	if (data->mov->mov_f)
	{
		data->player->x_pos += data->player->x_look * 0.05;
		data->player->y_pos += data->player->y_look * 0.05;
	}
	if (data->mov->mov_b)
	{
		data->player->x_pos -= data->player->x_look * 0.05;
		data->player->y_pos -= data->player->y_look * 0.05;
	}
	if (data->mov->mov_l)
	{
		data->player->x_pos -= data->player->y_look * 0.05 * 0.66; // change for plane
		data->player->y_pos += data->player->x_look * 0.05 * 0.66;
	}
	if (data->mov->mov_r)
	{
		data->player->x_pos += data->player->y_look * 0.05 * 0.66; // change for plane
		data->player->y_pos -= data->player->x_look * 0.05 * 0.66;
	}

}


int	ft_frame_render(t_data *data)
{
	while (ft_get_time_in_ms() <= data->time_frame)
		;
	data->time_frame += 17;
	ft_player_mov(data);
	data->ray->dirX = data->player->x_look;
	data->ray->dirY = data->player->y_look;
	data->ray->posX = data->player->x_pos;
	data->ray->posY = data->player->y_pos;
	data->ray->planeX = data->ray->dirY * 0.66;
	data->ray->planeY = -data->ray->dirX * 0.66;
    for(int x = 0; x < WIN_WIDTH; x += 1)
    {
		data->ray->cameraX = (x << 1) / (double)WIN_WIDTH - 1;
		data->ray->rayDirX = data->ray->dirX + data->ray->planeX * data->ray->cameraX;
		data->ray->rayDirY = data->ray->dirY + data->ray->planeY * data->ray->cameraX;
		data->ray->mapX = (int) data->ray->posX;
		data->ray->mapY = (int) data->ray->posY;
		data->ray->hit = 0;
		data->ray->deltaDistX = (data->ray->rayDirX == 0) ? 1e30 : fabs(1 / data->ray->rayDirX);
		data->ray->deltaDistY = (data->ray->rayDirY == 0) ? 1e30 : fabs(1 / data->ray->rayDirY);
		if(data->ray->rayDirX < 0)
		{
			data->ray->stepX = -1;
			data->ray->sideDistX = (data->ray->posX - data->ray->mapX) * data->ray->deltaDistX;
		}
		else
		{
			data->ray->stepX = 1;
			data->ray->sideDistX = (data->ray->mapX + 1.0 - data->ray->posX) * data->ray->deltaDistX;
		}
		if(data->ray->rayDirY < 0)
		{
			data->ray->stepY = -1;
			data->ray->sideDistY = (data->ray->posY - data->ray->mapY) * data->ray->deltaDistY;
		}
		else
		{
			data->ray->stepY = 1;
			data->ray->sideDistY = (data->ray->mapY + 1.0 - data->ray->posY) * data->ray->deltaDistY;
		}
		while(data->ray->hit == 0)
		{
			if(data->ray->sideDistX < data->ray->sideDistY)
			{
				data->ray->sideDistX += data->ray->deltaDistX;
				data->ray->mapX += data->ray->stepX;
				data->ray->side = 0;
			}
			else
			{
				data->ray->sideDistY += data->ray->deltaDistY;
				data->ray->mapY += data->ray->stepY;
				data->ray->side = 1;
			}
			if(data->map[data->ray->mapX][data->ray->mapY] == '1')
				data->ray->hit = 1;
		}
		if(data->ray->side == 0) data->ray->perpWallDist = (data->ray->sideDistX - data->ray->deltaDistX);
		else          data->ray->perpWallDist = (data->ray->sideDistY - data->ray->deltaDistY);
		data->ray->lineHeight = (int)(WIN_HEIGHT / data->ray->perpWallDist);
		data->ray->drawStart = -(data->ray->lineHeight >> 1) + WIN_HEIGHT >> 1;
		if(data->ray->drawStart < 0)
			data->ray->drawStart = 0;
		data->ray->drawEnd = (data->ray->lineHeight >> 1) + WIN_HEIGHT >> 1;
		if(data->ray->drawEnd >= WIN_HEIGHT) data->ray->drawEnd = h - 1;
		data->ray->orien = get_wall_dir(data->ray->side, data->ray->stepX, data->ray->stepY);
		double wallX;
		if (data->ray->side == 0)
			wallX = data->ray->posY + data->ray->perpWallDist * data->ray->rayDirY;
		else
			wallX = data->ray->posX + data->ray->perpWallDist * data->ray->rayDirX;
		wallX -= floor(wallX);

		int texWidth = data->texture_wall->x;
		int texHeight = data->texture_wall->y;

		int texX = (int)(wallX * (double)texWidth);
		if (data->ray->side == 0 && data->ray->rayDirX > 0) texX = texWidth - texX - 1;
		if (data->ray->side == 1 && data->ray->rayDirY < 0) texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / data->ray->lineHeight;
		double texPos = (data->ray->drawStart - WIN_HEIGHT / 2 + data->ray->lineHeight / 2) * step;

		// Draw vertical stripe
		int y = -1;
		while (++y < data->ray->drawStart)
			data->img->addr[y * (data->img->size_line >> 2) + x] = data->hex_ceiling;

		while (y <= data->ray->drawEnd)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = data->texture_wall->addr[texY * (data->texture_wall->size_line >> 2) + texX];
//			if (data->ray->side == 1)
//				color = (color >> 1) & 0x7F7F7F;

			data->img->addr[y * (data->img->size_line >> 2) + x] = color;
			y++;
		}

		while (y < WIN_HEIGHT)
			data->img->addr[y++ * (data->img->size_line >> 2) + x] = data->hex_floor;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

void	init_texture_pixels(t_data *data)
{
	int	i;

	// if (data->tex_pix)
	// 	free_tab((void **)data->texture_pixels);
	data->tex_pix = ft_calloc(data->win_height + 1,
			sizeof * data->tex_pix);
	// 	clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	i = -1;
	while (i < data->win_height)
	{
		data->tex_pix[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pix);
		i++;
	}
}
