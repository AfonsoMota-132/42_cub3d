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
		tdata->data->zbuffer[x] = tdata->ray->perpWallDist;
        ft_line_height(tdata->ray, tdata->data);
        ft_pre_render_line(tdata->data, tdata->ray, x, -1);
    }
    return (NULL);
}

// void	ft_line_height_enemy(t_ray *ray, t_data *data)
// {
// 	if (ray->side == 0)
// 		ray->perpWallDist = (ray->sideDistX
// 				- ray->deltaDistX);
// 	else
// 		ray->perpWallDist = (ray->sideDistY
// 				- ray->deltaDistY);
// 	if (ray->hit == 2)
// 		ray->perpWallDist += 0.5; // Increase this (e.g., 0.5) if still too close
// 	ray->lineHeight = (int)(WIN_HEIGHT / ray->perpWallDist);
// 	if (ray->hit == 2)
// 		ray->lineHeight *= 0.6; // Try 0.6 for smaller enemies
// 	ray->drawStart = -(ray->lineHeight >> 1) + (WIN_HEIGHT >> 1) + data->player->angle_y;
// 	if (ray->drawStart < 0)
// 		ray->drawStart = 0;
// 	ray->drawEnd = (ray->lineHeight >> 1) + (WIN_HEIGHT >> 1) + data->player->angle_y;
// 	if (ray->drawEnd >= WIN_HEIGHT)
// 		ray->drawEnd = WIN_HEIGHT - 1;
// 	if (ray->side == 0)
// 		ray->orien = (ray->stepX <= 0);
// 	else
// 		ray->orien = 2 + (ray->stepY <= 0);
// }
// void	ft_render_line_enemy(int x, int y, t_line_improv_render line)
// {
// 	int	color;
//
// 	y = line.drawStart;
// 	while (++y <= line.drawEnd)
// 	{
// 		line.texPos += line.step;
// 		color = line.tex_addr[((int)line.texPos
// 			& (line.text_y)) * (line.tex_sl) + line.texX];
// 		if (color)
// 			line.addr[y * line.img_sl + x] = color; 
// 	}
// }

// void	ft_ray_render_line_enemy(t_ray *ray, t_data *data)
// {
// 	ray->wallX = (ray->posY + ray->perpWallDist
// 		* ray->rayDirY) * (ray->side == 0)
// 	+ (ray->posX + ray->perpWallDist * ray->rayDirX)
// 	* (ray->side != 0);
// 	ray->wallX -= floor(ray->wallX);
// 	ray->texX = (int)(ray->wallX * (double)data->texture_wall->x);
// 	ray->texX = ray->texX + ((ray->side == 0
// 				&& ray->rayDirX > 0) || (ray->side == 1
// 				&& ray->rayDirY < 0)) * (data->texture_wall->x
// 			- ray->texX - ray->texX - 1);
// }

// void	ft_pre_render_line_enemy(t_data *data, t_ray *ray, int x, int y)
// {
// 	t_line_improv_render	line;
//
// 	data->texture_wall = data->tex_enemy;
// 	ft_ray_render_line_enemy(ray, data);
// 	line.addr = data->img->addr;
// 	line.step = 1.0 * data->texture_wall->y / ray->lineHeight;
// 	line.texPos = (ray->drawStart - data->player->angle_y - (WIN_HEIGHT >> 1)
// 			+ (ray->lineHeight >> 1)) * line.step;
// 	line.hex_ceil = data->hex_ceiling;
// 	line.hex_floor = data->hex_floor;
// 	line.img_sl = (data->img->size_line >> 2);
// 	line.tex_sl = data->texture_wall->size_line >> 2;
// 	line.text_y = data->texture_wall->y - 1;
// 	line.tex_addr = data->texture_wall->addr;
// 	line.drawEnd = ray->drawEnd;
// 	line.drawStart = ray->drawStart;
// 	line.texX = ray->texX;
// 	ft_render_line_enemy(x, y, line);
// }

void ft_render_enemy_sprite(t_data *data, t_ray *ray, t_enemy *enemy)
{
	double dirX = data->player->x_look;
	double dirY = data->player->y_look;
	double planeX = ray->planeX;
	double planeY = ray->planeY;
    double spriteX = data->enemy->data->x_pos - data->ray->posX;
    double spriteY = data->enemy->data->y_pos - data->ray->posY;

	double invDet = 1.0 / (planeX * dirY - dirX * planeY);
	
	// Correct transform
	double transformX = invDet * (dirY * spriteX - dirX * spriteY);
	double transformY = invDet * (-planeY * spriteX + planeX * spriteY);
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
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * enemy->tex->x / spriteWidth) / 256;
        if (texX < 0) texX = 0;
        if (texX >= enemy->tex->x) texX = enemy->tex->x - 1;
		if (transformY > 0 && stripe > 0 && stripe < WIN_WIDTH && transformY < data->zbuffer[stripe + 1])
        {
            for (int y = drawStartY; y < drawEndY + 1; y++)
            {
                int d = (y - data->player->angle_y) * 256 - WIN_HEIGHT * 128 + spriteHeight * 128;
                int texY = ((d * enemy->tex->y) / spriteHeight) / 256;
                if (texY < 0) texY = 0;
                if (texY >= enemy->tex->y) texY = enemy->tex->y - 1;

                int color = enemy->tex->addr[texY * enemy->tex->x + texX];
				if (color != 0x000000)
				{
					data->zbuffer[stripe] = transformY;
                    data->img->addr[y * WIN_WIDTH + stripe] = color;
				}
            }
        }
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
		if (data->map[ray->mapX][ray->mapY] == 'P')
				ray->hit = 3;
		if (data->map[ray->mapX][ray->mapY] == '1')
			ray->hit = 1;
	}
}

void	ft_raycasting_enemies(t_data *data, t_enemy *enemy)
{
	double	tempx;
	double	tempy;
	int		x = -1;
	int		first_x = -1;
	double dx = enemy->data->x_pos - data->player->x_pos;
	double dy = enemy->data->y_pos - data->player->y_pos;
	double	dist_sq = (dx * dx) + (dy * dy);
	
	if (enemy->map == '0')
		return ;
	while (++x < WIN_WIDTH)
	{
		ft_pre_render_loop(enemy->ray, enemy->data);
		ft_set_ray_loop(enemy->ray, x);
		ft_ray_dir(enemy->ray);
		ft_dda_enemies(enemy->ray, data);
		if (enemy->ray->hit == 3 && first_x == -1)
			first_x = x;
		else if (enemy->ray->hit == 1 && first_x != -1)
			break ;
	}
	if (first_x != -1 || data->map[(int) enemy->data->x_pos][(int) enemy->data->y_pos] == 'P')
	{
		enemy->ray->sideDistX = fabs(data->player->y_pos - enemy->data->x_pos);
		enemy->ray->sideDistX = fabs(data->player->y_pos - enemy->data->y_pos);
		x = (x + first_x) / 2;
		if (x > (WIN_WIDTH / 2) && first_x != -1)
		{
			enemy->data->angle = ft_add_angle(enemy->data->angle, +2.5);
			enemy->data->y_look = cos(enemy->data->angle * M_PI / 180.0);
			enemy->data->x_look = sin(enemy->data->angle * M_PI / 180.0);
		}
		if (x < (WIN_WIDTH / 2) && first_x != -1)
		{
			enemy->data->angle = ft_add_angle(enemy->data->angle, -2.5);
			enemy->data->y_look = cos(enemy->data->angle * M_PI / 180.0);
			enemy->data->x_look = sin(enemy->data->angle * M_PI / 180.0);
		}
		if ((x < WIN_WIDTH / 2 || x > WIN_WIDTH / 2)
			|| (enemy->ray->sideDistX > 1 && enemy->ray->sideDistY > 1)
			|| (dist_sq < 1 && dist_sq > 0.5))
		{
			tempx = enemy->data->x_pos + enemy->data->x_look * 0.01;
			tempy = enemy->data->y_pos + enemy->data->y_look * 0.01;
			if (ft_ver_col(data->map, tempx, tempy, enemy->map))
			{
				enemy->data->x_pos = tempx;
				enemy->data->y_pos = tempy;
			}
		}
		if ((data->map[(int) enemy->data->x_pos][ (int) enemy->data->y_pos] != 'A'))
		{
		if (data->map[(int) enemy->data->x_pos][ (int) enemy->data->y_pos] != 'P')
			data->map[(int) enemy->data->x_pos][(int) enemy->data->y_pos] = enemy->map;
		if (data->map[(int) enemy->data->x_pos + 1][(int) enemy->data->y_pos] == enemy->map)
			data->map[(int) enemy->data->x_pos + 1][(int) enemy->data->y_pos] = '0';
		if (data->map[(int) enemy->data->x_pos - 1][(int) enemy->data->y_pos] == enemy->map)
			data->map[(int) enemy->data->x_pos - 1][(int) enemy->data->y_pos] = '0';	
		if (data->map[(int) enemy->data->x_pos][(int) enemy->data->y_pos + 1] == enemy->map)
			data->map[(int) enemy->data->x_pos][(int) enemy->data->y_pos + 1] = '0';
		if (data->map[(int) enemy->data->x_pos][(int) enemy->data->y_pos - 1] == enemy->map)
			data->map[(int) enemy->data->x_pos][(int) enemy->data->y_pos - 1] = '0';
		}
	}
}

void	*ft_enemy_render_threads(void *arg)
{
	t_enemy	*enemy;
	t_data	*data;
	int x = - 1;

	enemy = (t_enemy *) arg;
	data = enemy->rdata;
	enemy->render = false;
	enemy->visible = false;
	if (enemy->map == '0')
		return (NULL);
	ft_pre_render_loop(enemy->ray, data->player);
	while (++x < WIN_WIDTH)
	{
		ft_set_ray_loop(enemy->ray, x);
		ft_ray_dir(enemy->ray);
		ft_dda_enemy(enemy->ray, data, enemy->map);
		if (enemy->ray->hit == 2)
		{
			if (ft_get_time_in_ms() > enemy->next_frame)
			{
				if (enemy->frame == 0)
				{
					enemy->tex = enemy->tex_iddle->sprite1;
					enemy->frame = 1;
				}
				else if (enemy->frame == 1)
				{
					enemy->tex = enemy->tex_iddle->sprite2;
					enemy->frame = 2;
				}
				else if (enemy->frame == 2)
				{
					enemy->tex = enemy->tex_iddle->sprite3;
					enemy->frame = 3;
				}
				else if (enemy->frame == 3)
				{
					enemy->tex = enemy->tex_iddle->sprite4;
					enemy->frame = 4;
				}
				else if (enemy->frame == 4)
				{
					enemy->tex = enemy->tex_iddle->sprite5;
					enemy->frame = 5;
				}
				else if (enemy->frame == 5)
				{
					enemy->tex = enemy->tex_iddle->sprite6;
					enemy->frame = 0;
				}
				enemy->next_frame = ft_get_time_in_ms() + 133.66f;
			}
			ft_render_enemy_sprite(data, enemy->ray, enemy);
			break ;
		}
	}
	ft_raycasting_enemies(data, enemy);
	return (NULL);
}

void	ft_sort_enemies(t_data *data)
{
	int		i;
	t_enemy	*tmp;
	int		dist1;
	int		dist2;

	tmp = data->enemy_arr[0];
	i = -1;
	while (data->enemy_arr[++i + 1])
	{
		dist1 = sqrt(pow(data->player->x_pos - data->enemy_arr[i]->data->x_pos, 2)
			   + pow(data->player->y_pos - data->enemy_arr[i]->data->y_pos, 2));
		dist2 = sqrt(pow(data->player->x_pos - data->enemy_arr[i + 1]->data->x_pos, 2)
			   + pow(data->player->y_pos - data->enemy_arr[i + 1]->data->y_pos, 2));
		if (dist1 < dist2)
		{
			tmp = data->enemy_arr[i];
			data->enemy_arr[i] = data->enemy_arr[i + 1];
			data->enemy_arr[i + 1] = tmp; 
			i = -1;
		}
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

void	ft_shoot_raycasting(t_data *data)
{
	int	i;
	// int	x;
	char	enemy;
	int	hit = WIN_WIDTH / 2;
	int is_moving = data->mov->mov || data->mov->look;
	
	// Example: ±3px if still, ±15px if moving
	int max_offset = is_moving ? 150 : 3;
	
	int spread = (rand() % (2 * max_offset + 1)) - max_offset;
	
	hit += spread;
	
	// Clamp to screen bounds
	if (hit < 0) hit = 0;
	if (hit >= WIN_WIDTH) hit = WIN_WIDTH - 1;
	ft_pre_render_loop(data->ray, data->player);
	ft_set_ray_loop(data->ray, hit);
	ft_ray_dir(data->ray);
	enemy = ft_dda_shoot(data->ray, data);
	if (enemy)
	{
		i = -1;
		while (data->enemy_arr[++i])
		{
			if (data->enemy_arr[i]->map == enemy)
			{
				data->enemy_arr[i]->map = '0';
				data->map[(int) data->enemy_arr[i]->data->x_pos][(int) data->enemy_arr[i]->data->y_pos] = '0';
			}
		}
	}
}

void	ft_render_put_fps(t_img *img, t_img *nbr, int x_offset)
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
				img->addr[y * WIN_WIDTH + x + x_offset] = color;
		}
	}

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
		if (str[i] == '0')
			ft_render_put_fps(data->img, data->nbrs->nbr_0, offset);
		else if (str[i] == '1')
			ft_render_put_fps(data->img, data->nbrs->nbr_1, offset);
		else if (str[i] == '2')
			ft_render_put_fps(data->img, data->nbrs->nbr_2, offset);
		else if (str[i] == '3')
			ft_render_put_fps(data->img, data->nbrs->nbr_3, offset);
		else if (str[i] == '4')
			ft_render_put_fps(data->img, data->nbrs->nbr_4, offset);
		else if (str[i] == '5')
			ft_render_put_fps(data->img, data->nbrs->nbr_5, offset);
		else if (str[i] == '6')
			ft_render_put_fps(data->img, data->nbrs->nbr_6, offset);
		else if (str[i] == '7')
			ft_render_put_fps(data->img, data->nbrs->nbr_7, offset);
		else if (str[i] == '8')
			ft_render_put_fps(data->img, data->nbrs->nbr_8, offset);
		else if (str[i] == '9')
			ft_render_put_fps(data->img, data->nbrs->nbr_9, offset);
		offset += 16;
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
	ft_sort_enemies(data);
	if (data->mov->shoot)
		ft_shoot_raycasting(data);
	i = -1;
	while (data->enemy_arr[++i])
		ft_enemy_render_threads(data->enemy_arr[i]);
	ft_pre_render_loop(data->ray, data->player);
	ft_put_fps(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	data->mov->mov = false;
	data->mov->look = false;
	data->mov->shoot = false;
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
