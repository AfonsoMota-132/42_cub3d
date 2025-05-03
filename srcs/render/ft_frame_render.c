/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:49:26 by afogonca          #+#    #+#             */
/*   Updated: 2025/04/26 09:54:48 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	ft_frame_render(t_data *data)
{
	double dirX = data->player->x_look;
	double dirY = data->player->y_look;
	double posX = data->player->x_pos;
	double posY = data->player->y_pos;
	double planeX = dirY * 0.66, planeY = -dirX * 0.66;
	ft_set_bg(data);
    for(int x = 0; x < WIN_WIDTH; x += 1)
    {
		double cameraX = 2 * x / (double)WIN_WIDTH - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		int	mapX = (int) posX;
		int	mapY = (int) posY;
		double sideDistX;
		double sideDistY;
		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(data->map[mapX][mapY] == '1') hit = 1;
		}
		// printf("mapY: %d\tmapX: %d\tchar: %c\n", mapY, mapX,data->map[mapX][mapY]);
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if(drawEnd >= h) drawEnd = h - 1;
		int	color;
		int	orien;
		orien = get_wall_dir(side, stepX, stepY);
		color = 0xFF0000;
		if (orien == 0)       // West wall
			color = 0xFF0000; // Red
		else if (orien == 1)  // East wall
			color = 0x00FF00; // Green
		else if (orien == 2)  // North wall
			color = 0x0000FF; // Blue
		else                  // South wall
			color = 0xFFFF00; // Yellow
		while (drawStart <= drawEnd)
		{
			ft_set_image_pixel(data->img, x, drawStart, color);
			drawStart++;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

void	ft_set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	init_texture_pixels(t_data *data)
{
	int	i;

	// if (data->tex_pix)
	// 	free_tab((void **)data->texture_pixels);
	data->tex_pix = ft_calloc(data->win_height + 1,
			sizeof * data->tex_pix);
	// 	clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	i = 0;
	while (i < data->win_height)
	{
		data->tex_pix[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pix);
		i++;
	}
}
