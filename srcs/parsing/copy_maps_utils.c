/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_maps_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:34:36 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 13:19:15 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_map(char **line, int i, int fd)
{
	if (i)
		free(*line);
	*line = get_next_line(fd);
}

void	copy_map_utils(t_data *data, int fd, char *line)
{
	int	i;

	i = -1;
	while (line)
	{
		data->map->map[++i] = string_copy(line);
		data->map->matrix[i] = string_copy(line);
		if (!check_line(line))
		{
			while (line)
				free_map(&line, 1, fd);
			data->map->map[++i] = NULL;
			data->map->matrix[i] = NULL;
			ft_putstr_fd("Error!\nNo valid Map after textures/colors!\n",
				2);
			ft_free(1, data);
		}
		free_map(&line, 1, fd);
	}
	data->map->map[++i] = NULL;
	data->map->matrix[i] = NULL;
	close(fd);
}
