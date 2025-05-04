/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:40:02 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/01 16:27:11 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

double ft_get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

t_data	*ft_data_init(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->img = NULL;
	data->tex_north = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->player = NULL;
	data->ray = NULL;
	data->mov = NULL;
	data->map = NULL;
	data->hex_ceiling = 0;
	data->hex_floor = 0;
	data->time_frame = 0;

	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		ft_free(-1, data);
	data->hex_ceiling = 0x0000FF;
	data->hex_floor = 0xFF0000;

	data->map = malloc(sizeof(char *) * 7);
	if (!data->map)
		ft_free(-1, data);
	data->map[0] = ft_strdup("1111111");
	data->map[1] = ft_strdup("1010101");
	data->map[2] = ft_strdup("1000001");
	data->map[3] = ft_strdup("1000001");
	data->map[4] = ft_strdup("100N001");
	data->map[5] = ft_strdup("1111111");
	data->map[6] = NULL; //should put malloc protection here but gonna leave it because its gonna be joanas part
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
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		ft_free(-1, data);
	data->player->x_pos = 4.5;
	data->player->y_pos = 3.5;
	data->player->angle = 300;
	data->player->y_look = cos(data->player->angle * M_PI / 180.0);
	data->player->x_look = sin(data->player->angle * M_PI / 180.0);
	data->time_frame = ft_get_time_in_ms() + 17;
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
	data->img->img = mlx_new_image(data->mlx, 1280, 720);
	if (!data->img->img)
		ft_free(-1, data);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->pixel_bits,
			&data->img->size_line, &data->img->endian);


	data->tex_north = malloc(sizeof(t_img));
	if (!data->tex_north)
		ft_free(-1, data);
	data->tex_north->img = NULL;
	data->tex_north->img = mlx_xpm_file_to_image(data->mlx, "tex/north.xpm", &data->tex_north->x, &data->tex_north->y);
	if (!data->tex_north->img)
		ft_free(-1, data);
	data->tex_north->addr = (int *)mlx_get_data_addr(data->tex_north->img, &data->tex_north->pixel_bits, &data->tex_north->size_line, &data->tex_north->endian);

	data->tex_south = malloc(sizeof(t_img));
	if (!data->tex_south)
		ft_free(-1, data);
	data->tex_south->img = NULL;
	data->tex_south->img = mlx_xpm_file_to_image(data->mlx, "tex/south.xpm", &data->tex_south->x, &data->tex_south->y);
	if (!data->tex_south->img)
		ft_free(-1, data);
	data->tex_south->addr = (int *)mlx_get_data_addr(data->tex_south->img, &data->tex_south->pixel_bits, &data->tex_south->size_line, &data->tex_south->endian);
	
	data->tex_east = malloc(sizeof(t_img));
	if (!data->tex_east)
		ft_free(-1, data);
	data->tex_east->img = NULL;
	data->tex_east->img = mlx_xpm_file_to_image(data->mlx, "tex/east.xpm", &data->tex_east->x, &data->tex_east->y);
	if (!data->tex_east->img)
		ft_free(-1, data);
	data->tex_east->addr = (int *)mlx_get_data_addr(data->tex_east->img, &data->tex_east->pixel_bits, &data->tex_east->size_line, &data->tex_east->endian);

	data->tex_west = malloc(sizeof(t_img));
	if (!data->tex_west)
		ft_free(-1, data);
	data->tex_west->img = NULL;
	data->tex_west->img = mlx_xpm_file_to_image(data->mlx, "tex/west.xpm", &data->tex_west->x, &data->tex_west->y);
	if (!data->tex_west->img)
		ft_free(-1, data);
	data->tex_west->addr = (int *)mlx_get_data_addr(data->tex_west->img, &data->tex_west->pixel_bits, &data->tex_west->size_line, &data->tex_west->endian);
	mlx_do_key_autorepeatoff(data->mlx);
	data->texture_wall = data->tex_north;
	return (data);
}


