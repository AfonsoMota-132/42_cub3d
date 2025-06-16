/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:37:58 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 13:23:10 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	ft_free_img(t_data *data)
{
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
}

void	ft_free_doors(t_data *data)
{
	t_door	*tmp;

	while (data->head_door)
	{
		tmp = data->head_door->next;
		free(data->head_door);
		data->head_door = tmp;
	}
}

void	ft_free_map_data(t_data *data)
{
	if (data->map_data)
	{
		if (data->map_data->no)
			free(data->map_data->no);
		if (data->map_data->so)
			free(data->map_data->so);
		if (data->map_data->ea)
			free(data->map_data->ea);
		if (data->map_data->we)
			free(data->map_data->we);
		if (data->map_data->c)
			free(data->map_data->c);
		if (data->map_data->f)
			free(data->map_data->f);
		free(data->map_data);
	}
}

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
