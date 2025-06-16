/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:37:58 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 09:38:41 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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

void	ft_free_map_data(t_data *data)
{
	if (data->map_data)
	{
		if (data->map_data->NO)
			free(data->map_data->NO);
		if (data->map_data->SO)
			free(data->map_data->SO);
		if (data->map_data->EA)
			free(data->map_data->EA);
		if (data->map_data->WE)
			free(data->map_data->WE);
		if (data->map_data->C)
			free(data->map_data->C);
		if (data->map_data->F)
			free(data->map_data->F);
		free(data->map_data);
	}
}
