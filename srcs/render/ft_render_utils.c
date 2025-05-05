#include "ft_render.h"

void	ft_player_rot(t_data *data)
{
	if (data->mov->lookl)
	{
		data->mov->mov = true;
		data->player->angle = ft_add_angle(data->player->angle, -2.5);
		data->player->y_look = cos(data->player->angle * M_PI / 180.0);
		data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	}
	if (data->mov->lookr)
	{
		data->mov->mov = true;
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
		data->mov->mov = true;
		data->player->x_pos += data->player->x_look * 0.05;
		data->player->y_pos += data->player->y_look * 0.05;
	}
	if (data->mov->mov_b)
	{
		data->mov->mov = true;
		data->player->x_pos -= data->player->x_look * 0.05;
		data->player->y_pos -= data->player->y_look * 0.05;
	}
	if (data->mov->mov_l)
	{
		data->mov->mov = true;
		data->player->x_pos -= data->ray->planeX * 0.05;
		data->player->y_pos -= data->ray->planeY * 0.05;
	}
	if (data->mov->mov_r)
	{
		data->mov->mov = true;
		data->player->x_pos += data->ray->planeX * 0.05;
		data->player->y_pos += data->ray->planeY * 0.05;
	}	
}

void	ft_ray_dir(t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - ray->mapX)
			* ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - ray->posX)
			* ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - ray->mapY)
			* ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - ray->posY)
			* ray->deltaDistY;
	}
}

void	ft_set_ray_loop(t_ray *ray, int x)
{
	ray->cameraX = (2 * x / (double)WIN_WIDTH - 1) * ((double)WIN_WIDTH / WIN_HEIGHT);
	ray->rayDirX = ray->dirX + ray->planeX
		* ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY
		* ray->cameraX;
	ray->mapX = (int) ray->posX;
	ray->mapY = (int) ray->posY;
	ray->hit = 0;
	ray->deltaDistX = fabs(1 / (ray->rayDirX
				+ (ray->rayDirX == 0) * 1e-30));
	ray->deltaDistY = fabs(1 / (ray->rayDirY
				+ (ray->rayDirY == 0) * 1e-30));
}

void	ft_pre_render_loop(t_data *data, t_ray *ray, t_player *player)
{
	while (ft_get_time_in_ms() <= data->time_frame)
		;
	data->time_frame += 17;
	ft_player_mov(data);
	ray->dirX = player->x_look;
	ray->dirY = player->y_look;
	ray->posX = player->x_pos;
	ray->posY = player->y_pos;
	ray->planeX = ray->dirY * 0.66;
	ray->planeY = -ray->dirX * 0.66;
}
