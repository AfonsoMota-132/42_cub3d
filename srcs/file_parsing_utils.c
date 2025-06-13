/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:15:31 by palexand          #+#    #+#             */
/*   Updated: 2025/06/14 00:15:35 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

bool	parse_textures_utils(t_data *data, char *line, int i)
{
	if (ft_strnstr(line, "NO", 2 + i))
		data->map_data->NO = ft_strdup(line + (3 + i));
	else if (ft_strnstr(line, "SO", 2 + i))
		data->map_data->SO = ft_strdup(line + 3 + i);
	else if (ft_strnstr(line, "WE", 2 + i))
		data->map_data->WE = ft_strdup(line + 3 + i);
	else if (ft_strnstr(line, "EA", 2 + i))
		data->map_data->EA = ft_strdup(line + 3 + i);
	else if (ft_strnstr(line, "F", 1 + i))
		data->map_data->F = ft_strdup(line + 2 + i);
	else if (ft_strnstr(line, "C", 1 + i))
		data->map_data->C = ft_strdup(line + 2 + i);
	else if (check_textures(data, 0) == TRUE)
		return (TRUE);
	return (FALSE);
}
