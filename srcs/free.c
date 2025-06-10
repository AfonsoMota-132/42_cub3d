/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:38:39 by palexand          #+#    #+#             */
/*   Updated: 2025/06/10 22:04:53 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->map.map)
	{
		i = 0;
		while (data->map.map[i])
		{
			free(data->map.map[i]);
			i++;
		}
		free(data->map.map);
	}
	if (data->map.matrix)
	{
		i = 0;
		while (data->map.matrix[i])
		{
			free(data->map.matrix[i]);
			i++;
		}
		free(data->map.matrix);
	}
	free(data->file);
	free(data->map_data.NO);
	free(data->map_data.EA);
	free(data->map_data.SO);
	free(data->map_data.WE);
	free(data->map_data.F);
	free(data->map_data.C);
	free(data);
}

void free_rgb(char **rgb)
{
	int i;

	if (!rgb)
		return ;
	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}
