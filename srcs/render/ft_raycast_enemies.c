/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_enemies.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:24:24 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:35:57 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void	ft_raycasting_enemies_utils(t_data *data, t_enemy *enemy, \
				int x, int first_x)
{
	double	dist_sq;
	int		tempx;
	int		tempy;

	dist_sq = ft_calc_dist_sq(data, enemy);
	if (first_x != -1
		|| data->map[(int) enemy->data->x_pos][(int) enemy->data->y_pos] == 'P')
	{
		ft_raycasting_enemies_utils2(data, enemy, x, first_x);
		if ((x < data->width / 2 || x > data->width / 2)
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
		ft_raycasting_enemies_utils3(data, enemy);
	}
}

void	ft_raycasting_enemies(t_data *data, t_enemy *enemy)
{
	int		x;
	int		first_x;

	x = -1;
	first_x = -1;
	if (enemy->map == '0')
		return ;
	while (++x < data->width)
	{
		ft_pre_render_loop(enemy->ray, enemy->data, data);
		ft_set_ray_loop(enemy->ray, x, enemy->rdata);
		ft_ray_dir(enemy->ray);
		ft_dda_enemies(enemy->ray, data);
		if (enemy->ray->hit == 3 && first_x == -1)
			first_x = x;
		else if (enemy->ray->hit == 1 && first_x != -1)
			break ;
	}
}

void	ft_select_enemy_sprite2(t_enemy *enemy)
{
	if (enemy->frame == 3)
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
}

void	ft_select_enemy_sprite(t_enemy *enemy)
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
		else
			ft_select_enemy_sprite2(enemy);
		enemy->next_frame = ft_get_time_in_ms() + 133.66f;
	}
}

void	*ft_enemy_render_threads(void *arg)
{
	t_enemy	*enemy;
	t_data	*data;
	int		x;

	x = -1;
	enemy = (t_enemy *) arg;
	data = enemy->rdata;
	if (enemy->map == '0')
		return (NULL);
	ft_pre_render_loop(enemy->ray, data->player, data);
	while (++x < data->width)
	{
		ft_set_ray_loop(enemy->ray, x, data);
		ft_ray_dir(enemy->ray);
		ft_dda_enemy(enemy->ray, data, enemy->map);
		if (enemy->ray->hit == 2)
		{
			ft_select_enemy_sprite(enemy);
			ft_pre_render_enemy_sprite(data, enemy->ray, enemy);
			break ;
		}
	}
	ft_raycasting_enemies(data, enemy);
	return (NULL);
}
