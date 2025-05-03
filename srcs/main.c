/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:48:16 by afogonca          #+#    #+#             */
/*   Updated: 2025/04/26 09:55:07 by afogonca         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	get_wall_dir(int side, int stepX, int stepY)
{
	if (side == 0)
	{
		if (stepX > 0)
			return (0);  // Ray moved right (+X), hit West wall
		else
			return (1);  // Ray moved left (-X), hit East wall
	}
	else
	{
		if (stepY > 0)
			return (2); // Ray moved down (+Y), hit North wall
		else
			return (3); // Ray moved up (-Y), hit South wall
	}
}

int	key_hook_relea(int key, t_data *data)
{
	if (key == 119)
		data->mov->mov_f = false;
	if (key == 97)
		data->mov->mov_l = false;
	if (key == 115)
		data->mov->mov_b = false;
	if (key == 100)
		data->mov->mov_r = false;
	if (key == 65361)
		data->mov->lookl = false;
	if (key == 65363)
		data->mov->lookr = false;
	return (0);
}
int	main(void)
{
	t_data *data;
	int idk = 64;

	data = ft_data_init();
	data->mlx = mlx_init();
	data->img = malloc(sizeof(t_img));
	data->img->img = mlx_new_image(data->mlx, 1280, 720);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->pixel_bits,
			&data->img->size_line, &data->img->endian);
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3d");
	data->texture_wall = malloc(sizeof(t_img));
	data->texture_wall->img = mlx_xpm_file_to_image(data->mlx, "mossy.xpm", &data->texture_wall->x, &data->texture_wall->y);
	data->texture_wall->addr = (int *)mlx_get_data_addr(data->texture_wall->img, &data->texture_wall->pixel_bits, &data->texture_wall->size_line, &data->texture_wall->endian);
	printf("%c\n", data->map[(int)data->player->x_pos][(int)data->player->y_pos]);
	mlx_do_key_autorepeatoff(data->mlx);
	// mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win, 2, 1L<<0, &key_hook_press, data);
	mlx_hook(data->win, 3, 1L<<1, &key_hook_relea, data);
	mlx_loop_hook(data->mlx, &ft_frame_render, data);
	mlx_loop(data->mlx);
	// ft_frame_render(data);
}
