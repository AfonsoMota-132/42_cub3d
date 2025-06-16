/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:40:02 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 12:36:45 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	ft_set_data_null(t_data *data)
{
	data->img = NULL;
	data->tex_north = NULL;
	data->tex_south = NULL;
	data->tex_east = NULL;
	data->tex_west = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->player = NULL;
	data->ray = NULL;
	data->mov = NULL;
	data->map = NULL;
	data->file = NULL;
	data->map_data = NULL;
}

void	ft_init_ray_map(t_data *data, char *file)
{
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		ft_free(-1, data);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		ft_free(-1, data);
	data->map->map = NULL;
	data->map->matrix = NULL;
	data->map_data = malloc(sizeof(t_map_data));
	if (!data->map_data)
		ft_free(-1, data);
	data->map_data->line_position = 0;
	data->map_data->no = NULL;
	data->map_data->so = NULL;
	data->map_data->we = NULL;
	data->map_data->ea = NULL;
	data->map_data->f = NULL;
	data->map_data->c = NULL;
	data->file = ft_strdup(file);
	if (!data->file)
		ft_free(-1, data);
}

t_data	*ft_data_init(char *file)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	ft_set_data_null(data);
	ft_init_ray_map(data, file);
	parse_cub_file(".cub", file, data, false);
	parse_textures(data);
	trim_and_check(data);
	rgb_int(data);
	copy_map(data, file);
	ft_init_mov(data);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		ft_free(-1, data);
	data->time_frame = ft_get_time_in_ms() + 17;
	ft_init_player(data);
	if (!check_flood(data))
		ft_free(1, data);
	ft_win_start(data);
	ft_init_doors(data);
	return (data);
}

void	ft_init_mov(t_data *data)
{
	data->mov = malloc(sizeof(t_mov));
	if (!data->mov)
		ft_free(-1, data);
	data->mov->mov_f = false;
	data->mov->mov_b = false;
	data->mov->mov_l = false;
	data->mov->mov_r = false;
	data->mov->lookl = false;
	data->mov->lookr = false;
	data->mov->mov = true;
	data->mov->exit = false;
	data->mov->exit_main = false;
	data->mov->mouse = 0;
	data->mov->open = false;
}

void	ft_win_start(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_free(-1, data);
	ft_init_tex_wall(data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->win)
		ft_free(-1, data);
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		ft_free(-1, data);
	data->img->img = NULL;
	data->img->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img->img)
		ft_free(-1, data);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img,
			&data->img->pixel_bits, &data->img->size_line, &data->img->endian);
	data->minimap_height = WIN_HEIGHT * 0.15;
	data->minimap_width = data->minimap_height;
	ft_init_minimap(data);
}
