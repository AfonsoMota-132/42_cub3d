/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:08 by palexand          #+#    #+#             */
/*   Updated: 2025/06/09 17:48:08 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	init_data(t_data *data, char *file)
{
	data->player_count = 0;
	data->map.max_width = 0;
	data->map.max_height = size_map(file, data);
	data->player.x = 0;
	data->player.y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->file = ft_strdup(file);
	data->map_data.line_position = 0;
	data->map_data.NO = NULL;
	data->map_data.SO = NULL;
	data->map_data.WE = NULL;
	data->map_data.EA = NULL;
	data->map_data.F = NULL;
	data->map_data.C = NULL;
}
/**/
/*void	find_map(t_data *data)*/
/*{*/
/**/
/*}*/
