/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:34:57 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/13 11:34:54 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	ft_free_map(t_map *map)
{
	int	i;

	i = -1;
	if (map)
	{
		if (map->map)
		{
			while (map->map[++i])
				free(map->map[i]);
			free(map->map);
		}
		i = -1;
		if (map->matrix)
		{
			while (map->matrix[++i])
				free(map->matrix[i]);
			free(map->matrix);
		}
		free(map);
	}
}

void	ft_free_tex(t_data *data)
{
	if (data->tex_north)
	{
		if (data->tex_north->img)
			mlx_destroy_image(data->mlx, data->tex_north->img);
		free(data->tex_north);
	}
	if (data->tex_south)
	{
		if (data->tex_south->img)
			mlx_destroy_image(data->mlx, data->tex_south->img);
		free(data->tex_south);
	}
	if (data->tex_east)
	{
		if (data->tex_east->img)
			mlx_destroy_image(data->mlx, data->tex_east->img);
		free(data->tex_east);
	}
	if (data->tex_west)
	{
		if (data->tex_west->img)
			mlx_destroy_image(data->mlx, data->tex_west->img);
		free(data->tex_west);
	}
}

void	ft_free_map_data(t_data *data)
{
	if (data->map_data)
	{
		if (data->map_data->NO)
			free(data->map_data->NO);
		if (data->map_data->SO)
			free(data->map_data->SO);
		if (data->map_data->EA)
			free(data->map_data->EA);
		if (data->map_data->WE)
			free(data->map_data->WE);
		if (data->map_data->C)
			free(data->map_data->C);
		if (data->map_data->F)
			free(data->map_data->F);
		free(data->map_data);
	}

}

void	ft_free_data(t_data *data)
{
	mlx_do_key_autorepeaton(data->mlx);
	if (data->img)
	{
		if (data->img->img)
			mlx_destroy_image(data->mlx, data->img->img);
		free(data->img);
	}
	if (data->img_minimap)
	{
		if (data->img_minimap->img)
			mlx_destroy_image(data->mlx, data->img_minimap->img);
		free(data->img_minimap);
	}

	ft_free_tex(data);
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	if (data->mov)
		free(data->mov);
	ft_free_map_data(data);
	ft_free_map(data->map);
	if (data->file)
		free(data->file);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
}

void	ft_free(int exit_flag, t_data *data)
{
	if (data)
		ft_free_data(data);
	if (exit_flag != -1 && exit_flag >= 0)
		exit (exit_flag);
	printf("Fatal error: failed to malloc\n");
	exit (1);
}
