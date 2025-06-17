/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tex_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:48:39 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 12:37:17 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	ft_init_minimap(t_data *data)
{
	data->img_minimap = malloc(sizeof(t_img));
	if (!data->img_minimap)
		ft_free(-1, data);
	data->img_minimap->img = NULL;
	data->img_minimap->img = mlx_new_image(data->mlx, data->minimap_width,
			data->minimap_height);
	if (!data->img_minimap->img)
		ft_free(-1, data);
	data->img_minimap->addr = (int *)mlx_get_data_addr(data->img_minimap->img,
			&data->img_minimap->pixel_bits, &data->img_minimap->size_line,
			&data->img_minimap->endian);
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
		tmp = ft_player_look(data->map->map[i]);
		ft_init_player_utils(data, tmp, i);
	}
	if (tmp && data->player->x_pos == -1
		&& data->player->y_pos == -1)
	{
		ft_putstr_fd("Error\nPlayer not found\n", 2);
		ft_free(1, data);
	}
}

void	ft_init_tex_wall(t_data *data)
{
	data->tex_north = malloc(sizeof(t_img));
	if (!data->tex_north)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_north, data->map_data->no);
	data->tex_south = malloc(sizeof(t_img));
	if (!data->tex_south)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_south, data->map_data->so);
	data->tex_east = malloc(sizeof(t_img));
	if (!data->tex_east)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_east, data->map_data->ea);
	data->tex_west = malloc(sizeof(t_img));
	if (!data->tex_west)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_west, data->map_data->we);
	data->tex_door = malloc(sizeof(t_img));
	if (!data->tex_door)
		ft_free(-1, data);
	ft_start_tex(data, data->tex_door, "textures/door.xpm");
	data->hex_ceiling = data->map_data->color_c;
	data->hex_floor = data->map_data->color_f;
}

void	ft_start_tex(t_data *data, t_img *img, char *file)
{
	img->img = NULL;
	img->img = mlx_xpm_file_to_image(data->mlx, file, &img->x, &img->y);
	if (!img->img)
	{
		ft_putstr_fd("Error\nInvalid Textures/Colors!\n", 2);
		ft_free(1, data);
	}
	img->addr = (int *)mlx_get_data_addr(img->img,
			&img->pixel_bits, &img->size_line, &img->endian);
}
