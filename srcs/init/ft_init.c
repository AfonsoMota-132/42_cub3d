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

#include "../../incs/cub3d.h"

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
	ft_data_set_def(data);
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		ft_free(-1, data);
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
	ft_mov_set_def(data->mov);
	data->player1 = malloc(sizeof(t_player));
	if (!data->player1)
		ft_free(-1, data);
	data->player1->x_pos = 4.5;
	data->player1->y_pos = 3.5;
	data->player1->angle = 300;
	data->player1->y_look = cos(data->player1->angle * M_PI / 180.0);
	data->player1->x_look = sin(data->player1->angle * M_PI / 180.0);
	data->player = data->player1;
	data->time_frame = ft_get_time_in_ms() + 17;
	ft_win_start(data);

	data->tex_north = malloc(sizeof(t_img));
	if (!data->tex_north)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_north, "north.xpm");

	data->tex_south = malloc(sizeof(t_img));
	if (!data->tex_south)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_south, "south.xpm");

	data->tex_east = malloc(sizeof(t_img));
	if (!data->tex_east)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_east, "east.xpm");

	data->tex_west = malloc(sizeof(t_img));
	if (!data->tex_west)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_west, "west.xpm");


	data->nbr_threads = 4;
	data->tdata = malloc(sizeof(t_thread_data) * data->nbr_threads + 1);
	data->thread = malloc(sizeof(pthread_t) * data->nbr_threads + 1);
	int	i = -1;
	while (++i < data->nbr_threads)
	{
		data->tdata[i].ray = malloc(sizeof(t_ray));
    	data->tdata[i].data = data;
    	data->tdata[i].start_x = i * WIN_WIDTH / data->nbr_threads;
    	data->tdata[i].end_x = (i + 1) * WIN_WIDTH / data->nbr_threads;
	}
	return (data);
}

void	ft_start_tex(t_data *data, t_img *img, char *file)
{
	img->img = NULL;
	img->img = mlx_xpm_file_to_image(data->mlx, file, &img->x, &img->y);
	if (!img->img)
		ft_free(-1, data);
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
}

void	ft_data_set_def(t_data *data)
{
	data->img = NULL;
	data->texture_wall = NULL;
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
	data->hex_ceiling = 0;
	data->hex_floor = 0;
	data->time_frame = 0;
	data->old_frame = 0;
	data->hex_ceiling = 0x0000FF; // change both for 0x000000 after parsing is done
	data->hex_floor = 0xFF0000;
}


