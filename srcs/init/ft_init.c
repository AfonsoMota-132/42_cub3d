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
	data->map = malloc(sizeof(char *) * 10);
	if (!data->map)
		ft_free(-1, data);
	data->map[0] = ft_strdup("1111111111");
	data->map[1] = ft_strdup("1B10100001");
	data->map[2] = ft_strdup("100A001101");
	data->map[3] = ft_strdup("1000001101");
	data->map[4] = ft_strdup("100P000001");
	data->map[5] = ft_strdup("100100R001");
	data->map[6] = ft_strdup("1001001001");
	data->map[7] = ft_strdup("1000001001");
	data->map[8] = ft_strdup("1111111111");
	data->map[9] = NULL; //should put malloc protection here but gonna leave it because its gonna be joanas part
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
	data->time_frame = ft_get_time_in_ms() + 17;

	data->portal = malloc(sizeof(t_player));
	if (!data->portal)
		ft_free(-1, data);
	data->portal->x_pos = 2;
	data->portal->y_pos = 1;
	data->portal->angle = 360;
	data->portal->y_look = cos(data->portal->angle * M_PI / 180.0);
	data->portal->x_look = sin(data->portal->angle * M_PI / 180.0);
	data->portal_ray = malloc(sizeof(t_ray));

	data->enemy_arr = malloc(sizeof(t_enemy *) * 10);
	data->enemy_arr[0] = NULL;
	data->enemy_arr[1] = NULL;
	data->enemy_arr[2] = NULL;
	data->enemy_arr[3] = NULL;
	data->enemy_arr[4] = NULL;
	data->enemy_arr[5] = NULL;
	data->enemy_arr[6] = NULL;
	data->enemy_arr[7] = NULL;
	data->enemy_arr[8] = NULL;
	data->enemy_arr[9] = NULL;

	ft_win_start(data);
	data->enemy = malloc(sizeof(t_enemy));
	if (!data->enemy)
		ft_free(-1, data);
	data->enemy->map = 'E';
	data->enemy->next = NULL;
	data->enemy->data = malloc(sizeof(t_player));
	if (!data->enemy->data)
		ft_free(-1, data);
	data->enemy->data->x_pos = 2.5;
	data->enemy->data->y_pos = 3.5;
	data->enemy->data->angle = 100;
	data->enemy->map = 'A';
	data->enemy->ray = malloc(sizeof(t_ray));
	data->enemy->rdata = data;
	data->enemy->tex_iddle = malloc(sizeof(t_tex_iddle));
	data->enemy->tex_iddle->sprite1 = malloc(sizeof(t_img));
	if (!data->enemy->tex_iddle->sprite1)
		ft_free(-1, data);
	ft_start_tex(data, data->enemy->tex_iddle->sprite1, "idle1.xpm");

	data->enemy->tex_iddle->sprite2 = malloc(sizeof(t_img));
	if (!data->enemy->tex_iddle->sprite2)
		ft_free(-1, data);
	ft_start_tex(data, data->enemy->tex_iddle->sprite2, "idle2.xpm");

	data->enemy->tex_iddle->sprite3 = malloc(sizeof(t_img));
	if (!data->enemy->tex_iddle->sprite3)
		ft_free(-1, data);
	ft_start_tex(data, data->enemy->tex_iddle->sprite3, "idle3.xpm");

	data->enemy->tex_iddle->sprite4 = malloc(sizeof(t_img));
	if (!data->enemy->tex_iddle->sprite4)
		ft_free(-1, data);
	ft_start_tex(data, data->enemy->tex_iddle->sprite4, "idle4.xpm");
	data->enemy->tex = data->enemy->tex_iddle->sprite4;

	data->enemy->tex_iddle->sprite5 = malloc(sizeof(t_img));
	if (!data->enemy->tex_iddle->sprite5)
		ft_free(-1, data);
	ft_start_tex(data, data->enemy->tex_iddle->sprite5, "idle5.xpm");

	data->enemy->tex_iddle->sprite6 = malloc(sizeof(t_img));
	if (!data->enemy->tex_iddle->sprite6)
		ft_free(-1, data);
	ft_start_tex(data, data->enemy->tex_iddle->sprite6, "idle6.xpm");
	data->enemy->data->y_look = cos(data->enemy->data->angle * M_PI / 180.0);
	data->enemy->data->x_look = sin(data->enemy->data->angle * M_PI / 180.0);
	data->enemy->next_frame = 0;
	data->enemy->frame = 0;

	data->enemy_arr[0] = data->enemy;
	data->enemy_arr[1] = malloc(sizeof(t_enemy));
	if (!data->enemy_arr[1])
		ft_free(-1, data);
	data->enemy_arr[1]->map = 'E';
	data->enemy_arr[1]->next = NULL;
	data->enemy_arr[1]->data = malloc(sizeof(t_player));
	if (!data->enemy->data)
		ft_free(-1, data);
	data->enemy_arr[1]->data->x_pos = 1.5;
	data->enemy_arr[1]->data->y_pos = 1.5;
	data->enemy_arr[1]->data->angle = 100;
	data->enemy_arr[1]->map = 'B';
	data->enemy_arr[1]->rdata = data;
	data->enemy_arr[1]->ray = malloc(sizeof(t_ray));
	data->enemy_arr[1]->tex_iddle = data->enemy_arr[0]->tex_iddle;
	data->enemy_arr[1]->tex = data->enemy_arr[1]->tex_iddle->sprite1;
	data->enemy_arr[1]->data->y_look = cos(data->enemy_arr[1]->data->angle * M_PI / 180.0);
	data->enemy_arr[1]->data->x_look = sin(data->enemy_arr[1]->data->angle * M_PI / 180.0);

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

	data->nbr_threads = 8;
	data->tdata = malloc(sizeof(t_thread_data) * data->nbr_threads + 1);
	data->thread = malloc(sizeof(pthread_t) * data->nbr_threads + 1);
	int	i = -1;
	while (++i < data->nbr_threads)
	{
		data->tdata[i].ray = malloc(sizeof(t_ray));
    	data->tdata[i].data = data;
    	data->tdata[i].start_x = i * data->width / data->nbr_threads;
    	data->tdata[i].end_x = (i + 1) * data->width / data->nbr_threads;
	}
	data->player1->angle_y = 0;
	data->nbrs = malloc(sizeof(t_tex_nbrs));

	data->nbrs->nbr_0 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_0)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_0, "0.xpm");

	data->nbrs->nbr_1 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_1)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_1, "1.xpm");

	data->nbrs->nbr_2 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_2)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_2, "2.xpm");

	data->nbrs->nbr_3 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_3)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_3, "3.xpm");

	data->nbrs->nbr_4 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_4)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_4, "4.xpm");

	data->nbrs->nbr_5 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_5)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_5, "5.xpm");

	data->nbrs->nbr_6 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_6)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_6, "6.xpm");

	data->nbrs->nbr_7 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_7)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_7, "7.xpm");

	data->nbrs->nbr_8 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_8)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_8, "8.xpm");

	data->nbrs->nbr_9 = malloc(sizeof(t_img));
	if (!data->nbrs->nbr_9)
		ft_free(-1, data);
	ft_start_tex(data, data->nbrs->nbr_9, "9.xpm");

	data->tex_pause = malloc(sizeof(t_img));
	if (!data->tex_pause)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_pause, "menu.xpm");

	data->tex_pl = malloc(sizeof(t_img));
	if (!data->tex_pl)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_pl, "portal_blue.xpm");
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
	mov->mov = false;
	mov->look = true;
	mov->exit = false;
	mov->exit_main = false;
	mov->lookl = false;
	mov->lookr = false;
	mov->lookml = 0;
	mov->lookmr = 0;
	mov->sound = 0;
	mov->jump = 0;
	mov->shoot = 0;
	mov->pause = false;
	mov->time_sound = ft_get_time_in_ms();
}

void	ft_win_start(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_free(-1, data);
	data->win = mlx_new_window(data->mlx, data->width, data->height, "cub3d");
	if (!data->win)
		ft_free(-1, data);

	data->img_player = malloc(sizeof(t_img));
	if (!data->img_player)
		ft_free(-1, data);
	data->img_player->img = NULL;
	data->img_player->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img_player->img)
		ft_free(-1, data);
	data->img_player->addr = (int *)mlx_get_data_addr(data->img_player->img, &data->img_player->pixel_bits,
			&data->img_player->size_line, &data->img_player->endian);
	data->img = data->img_player;

	data->img_portal = malloc(sizeof(t_img));
	if (!data->img_portal)
		ft_free(-1, data);
	data->img_portal->img = NULL;
	data->img_portal->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img_portal->img)
		ft_free(-1, data);
	data->img_portal->addr = (int *)mlx_get_data_addr(data->img_portal->img, &data->img_portal->pixel_bits,
			&data->img_portal->size_line, &data->img_portal->endian);
	data->img_portal->x = data->width;
	data->img_portal->y = data->height;

	data->img_pause = malloc(sizeof(t_img));
	if (!data->img_pause)
		ft_free(-1, data);
	data->img_pause->img = NULL;
	data->img_pause->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img_pause->img)
		ft_free(-1, data);
	data->img_pause->addr = (int *)mlx_get_data_addr(data->img_pause->img,
			&data->img_pause->pixel_bits, &data->img_pause->size_line, &data->img_pause->endian);
	data->zbuffer = malloc(sizeof(double) * data->width);
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
	data->width = 1280;
	data->height = 720;
	data->frame_time = 0;
	data->see_portal = false;
}


