/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:34:57 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 13:02:56 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	free_rgb(char **rgb)
{
	int	i;

	if (!rgb)
		return ;
	i = -1;
	while (rgb[++i])
		free(rgb[i]);
	free(rgb);
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

void	ft_free_data(t_data *data)
{
	ft_free_img(data);
	ft_free_tex(data);
	ft_free_doors(data);
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
		mlx_do_key_autorepeaton(data->mlx);
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
	ft_putstr_fd("Fatal error: failed to malloc\n", 2);
	exit (1);
}
