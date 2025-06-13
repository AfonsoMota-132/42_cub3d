/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:40:02 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/13 11:31:22 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

double ft_get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

void	ft_init_tex_wall(t_data *data)
{
	data->tex_north = malloc(sizeof(t_img));
	if (!data->tex_north)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_north, data->map_data->NO);
	data->tex_south = malloc(sizeof(t_img));
	if (!data->tex_south)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_south, data->map_data->SO);
	data->tex_east = malloc(sizeof(t_img));
	if (!data->tex_east)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_east, data->map_data->EA);
	data->tex_west = malloc(sizeof(t_img));
	if (!data->tex_west)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_west, data->map_data->WE);
	data->hex_ceiling = data->map_data->color_c;
	data->hex_floor = data->map_data->color_f;
}

char	ft_player_look(char *line)
{
	if (ft_strchr(line, 'N'))
		return ('N');
	else if (ft_strchr(line, 'S'))
		return ('S');
	else if (ft_strchr(line, 'E'))
		return ('E');
	else if (ft_strchr(line, 'W'))
		return ('W');
	return ('\0');
}

void	ft_init_player(t_data *data)
{
	int		i;
	char	tmp;

	i = -1;
	while (data->map->map[++i])
	{
		tmp = ft_player_look(data->map->map[i])	;
		if (tmp)
		{
			data->player->x_pos = i + 0.5;
			data->player->y_pos = ft_strchr_len(data->map->map[i], tmp) + 0.5;
			data->player->angle = (tmp == 'N') * 270 + (tmp == 'S') * 90
				+ (tmp == 'W') * 180;
			break ;
		}
	}
	data->player->y_look = cos(data->player->angle * M_PI / 180.0);
	data->player->x_look = sin(data->player->angle * M_PI / 180.0);
}

void	ft_set_data_null(t_data *data)
{
	data->img = NULL;
	data->img_minimap = NULL;
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

t_door	*ft_new_door(int x, int y)
{
	t_door *new;

	new = malloc(sizeof(t_door));
	new->next = NULL;
	new->open = 0;
	new->pos = 0;
	new->x_pos = x;
	new->y_pos = y;
	return (new);
}

void	ft_door_add_back(t_door **door, int x, int y)
{
	t_door	*tmp;

	if (!*door)
		*door = ft_new_door(x, y);
	tmp = *door;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_new_door(x, y);
}

void	ft_init_doors(t_data *data)
{
	int	y;
	int	x;

	x = -1;
	while (data->map->map[++x])
	{
		y = -1;
		while (data->map->map[x][++y])
		{
			if (data->map->map[x][y] == 'H')
				ft_door_add_back(&data->head_door, x, y);
		}
	}
}

t_data	*ft_data_init(char *file)
{
	t_data *data;

	data = ft_calloc(sizeof(t_data), 1);
	ft_set_data_null(data);
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
	data->map_data->NO = NULL;
	data->map_data->SO = NULL;
	data->map_data->WE = NULL;
	data->map_data->EA = NULL;
	data->map_data->F = NULL;
	data->map_data->C = NULL;

	data->file = ft_strdup(file);
	if (!data->file)
		ft_free(-1, data);
	parse_cub_file(".cub", file, data);
	parse_textures(data);
	trim_and_check(data);
	rgb_int(data);
	copy_map(data, file);

	data->mov = malloc(sizeof(t_mov));
	if (!data->mov)
		ft_free(-1, data);

	ft_mov_set_def(data->mov);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		ft_free(-1, data);

	data->time_frame = ft_get_time_in_ms() + 17;
	ft_init_player(data);
	if (!check_flood(data))
		ft_free(1, data);
	ft_win_start(data);
	ft_init_tex_wall(data);
	data->map->map[(int)data->player->x_pos]\
		[(int)data->player->y_pos] = 'P';
	ft_init_doors(data);
	data->frame_time = ft_get_time_in_ms();
	return (data);
}

void	ft_start_tex(t_data *data, t_img *img, char *file)
{
	img->img = NULL;
	img->img = mlx_xpm_file_to_image(data->mlx, file, &img->x, &img->y);
	if (!img->img)
	{
		ft_putstr_fd("Error\nInvalid Textures/Colors!\n", 1);
		ft_free(1, data);
	}
	img->addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits, &img->size_line, &img->endian);
}

void	ft_mov_set_def(t_mov *mov)
{
	mov->mov_f = false;
	mov->mov_b = false;
	mov->mov_l = false;
	mov->mov_r = false;
	mov->lookl = false;
	mov->lookr = false;
	mov->mov = true;
	mov->exit = false;
	mov->exit_main = false;
	mov->open = false;
	mov->mouse = 0;
}

void	ft_win_start(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_free(-1, data);
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
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->pixel_bits,
			&data->img->size_line, &data->img->endian);
	data->minimap_height = WIN_HEIGHT * 0.15;
	data->minimap_width =  data->minimap_height;
	data->img_minimap = malloc(sizeof(t_img));
	if (!data->img_minimap)
		ft_free(-1, data);
	data->img_minimap->img = NULL;
	data->img_minimap->img = mlx_new_image(data->mlx, data->minimap_width, data->minimap_height);
	if (!data->img_minimap->img)
		ft_free(-1, data);
	data->img_minimap->addr = (int *)mlx_get_data_addr(data->img_minimap->img,
			&data->img_minimap->pixel_bits, &data->img_minimap->size_line,
			&data->img_minimap->endian);
}


