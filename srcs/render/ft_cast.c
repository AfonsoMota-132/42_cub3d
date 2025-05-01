/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:16:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/01 16:39:55 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	ft_calc_ray_side(t_data *data, t_ray *rays)
{

	if (rays->raydir_x < 0)
	{
		// esquerda
		rays->step_x = -1; // valor para
		rays->sidedist_x = (data->player->x_pos - rays->map_x) * rays->deltadist_x;
	}
	else
	{
		rays->step_x = 1;
		rays->sidedist_x = (rays->map_x + 1.0 - data->player->x_pos) * rays->deltadist_x;
	}
	if (rays->raydir_y < 0)
	{
		rays->step_y = -1; // baixo
		rays->sidedist_y = (data->player->y_pos - rays->map_y) * rays->deltadist_y;
	}
	else
	{
		rays->step_y = 1; // cima
		rays->sidedist_y = (rays->map_y + 1.0 - data->player->y_pos) * rays->deltadist_y;
	}
}

bool	ft_colision(float px, float py, t_data *data, int flag)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (flag == 1) // para mini mapa
	{
		x = (px / 5);
		y = (py / 5);
		if (data->map[y][x] == '1')
			return (true);
		return (false);
	}
	else
	{
		x = (px / BLOCK);
		y = (py / BLOCK);
		if (data->map[y][x] == '1')
			return (true);
		return (false);
	}
}

void	ft_calc_dda(t_data *cub, t_ray *rays)
{
	rays->hit = 0;
	while (rays->hit == 0)
	{
		if (rays->sidedist_x < rays->sidedist_y)
		{
			rays->sidedist_x += rays->deltadist_x;
			rays->map_x += rays->step_x;
			rays->side = 0;
		}
		else
		{
			rays->sidedist_y += rays->deltadist_y;
			rays->map_y += rays->step_y;
			rays->side = 1;
		}
		if (ft_colision(rays->map_x, rays->map_y, cub, 0))
			rays->hit = 1;
	}
}

void	ft_calc_draw_limitations_for_walls(t_data *data, t_rays *rays, int i)
{
	rays->line_height = (BLOCK * WIN_HEIGHT) / rays->perpwalldist;
	rays->draw_start = -rays->line_height / 2 + WIN_HEIGHT / 2;
	if (rays->draw_start < 0)
		rays->draw_start = 0;
	rays->draw_end = rays->line_height / 2 + WIN_HEIGHT / 2;
	if (rays->draw_end >= WIN_HEIGHT)
		rays->draw_end = WIN_HEIGHT - 1;
	if (rays->side == 0)
		rays->wall_x = data->player->y_pos + rays->perpwalldist * rays->raydir_y;
	else
		rays->wall_x = data->player->x_pos + rays->perpwalldist * rays->raydir_x;
}

void	calc_text_wall_pixel(t_data *data, t_ray *rays, int texture)
{
	rays->wall_x = fmod(rays->wall_x, BLOCK) / BLOCK;
	rays->tex_x = (int)((rays->wall_x) * ((double)data->img[texture].x));
	if ((rays->side == 0 && rays->raydir_x < 0))
		rays->tex_x = data->img[texture].x - rays->tex_x - 1;
	if (rays->side == 1 && rays->raydir_y > 0)
		rays->tex_x = data->img[texture].x - rays->tex_x - 1;
	rays->y = rays->draw_start;
	rays->step = 1.0 * data->imgs[texture].y / rays->line_height;
	rays->tex_pos = (rays->draw_start - WIN_HEIGHT / 2 + rays->line_height / 2)
		* rays->step;
}

void	handle_texture_calcs(t_data *data, t_ray *rays, int i)
{
	if (data->texture2apply == NORTH_TEXTURE)
		calc_text_wall_pixel(data, rays, NORTH_TEXTURE);
	else if (data->texture2apply == SOUTH_TEXTURE)
		calc_text_wall_pixel(data, rays, SOUTH_TEXTURE);
	else if (data->texture2apply == EAST_TEXTURE)
		calc_text_wall_pixel(data, rays, EAST_TEXTURE);
	else if (data->texture2apply == WEST_TEXTURE)
		calc_text_wall_pixel(data, rays, WEST_TEXTURE);
}

void	ft_calc_dist_wall(t_data *data, t_ray *rays, int i)
{
	if (rays->side == 0)
	{
		rays->perpwalldist = (rays->map_x - data->player->x_pos + (1 - rays->step_x) / 2)
			/ rays->raydir_x;
		if (rays->raydir_x > 0)
			data->txt2a = WEST;
		else
			data->txt2a = EAST;
	}
	else
	{
		rays->perpwalldist = (rays->map_y - data->player->y_pos + (1 - rays->step_y) / 2)
			/ rays->raydir_y;
		if (rays->raydir_y > 0)
			data->txt2a = NORTH;
		else
			data->txt2a = SOUTH;
	}
	ft_calc_draw_limitations_for_walls(data, rays, i);
	handle_texture_calcs(cub, &rays, i);
}

void	ft_cast(t_data *data, t_ray *ray, int i)
{
	ray->map_x = (int)data->player->x_pos;
	ray->map_y = (int)data->player->y_pos;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = cos(ray->angle);
	ray->camera_x = ((i << 1) / data->win_width - 1);
	ray->raydir_x = ray->dir_x + -ray->dir_x * tan((PI / 6)) * ray->camera_x;
	ray->raydir_y = ray->dir_y + ray->dir_y * tan((PI / 6)) * ray->camera_x;
	ray->deltadist_x = sqrt(1 + (ray->raydir_y * ray->raydir_y) / (ray->raydir_x
				* ray->raydir_x));
	ray->deltadist_y = sqrt(1 + (ray->raydir_x * ray->raydir_x) / (ray->raydir_y
				* ray->raydir_y));
}
