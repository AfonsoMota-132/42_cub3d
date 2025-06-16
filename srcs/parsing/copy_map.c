/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:29:37 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 09:36:11 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	check_line(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != '\n' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (FALSE);
	}
	return (TRUE);
}

// @brief	Function to check if the map is valid
// @param	data	Pointer to the data structure
// @return	Returns true if the map is valid, false otherwise
static bool	size_map(char *file, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error opening file", 2);
		ft_free(1, data);
	}
	i = -2;
	line = get_next_line(fd);
	i++;
	while (line)
	{
		free_map(&line, 1, fd);
		i++;
	}
	i -= data->map_data->line_position;
	data->map->max_height = i;
	if (i <= 0)
		return (false);
	data->map->map = ft_calloc(sizeof(t_map), i);
	data->map->matrix = ft_calloc(sizeof(t_map), i);
	return (close(fd), true);
}

char	*string_copy(char *line)
{
	char	*copy;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	j = ft_strlen(line);
	copy = (char *)malloc(sizeof(char) * (j));
	while (line[j] == ' ' || line[j] == '\t' || line[j] == '\n')
		j--;
	while (line[i] && line[i] != '\n' && i < j)
	{
		if (line[i] == '\n')
			break ;
		copy[i] = line[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	copy_map(t_data *data, char *file)
{
	int		i;
	int		fd;
	char	*line;

	if (size_map(file, data))
	{
		fd = open(file, O_RDONLY);
		i = -1;
		line = NULL;
		while (i++ <= data->map_data->line_position)
			free_map(&line, i, fd);
		while (line && !ft_strchr(line, '1'))
			free_map(&line, 1, fd);
		if (!line)
		{
			ft_putstr_fd("Error!\nNo valid Map!\n", 2);
			ft_free(1, data);
		}
		copy_map_utils(data, fd, line);
	}
	else
	{
		ft_putstr_fd("Error!\nNo valid Map/map after textures/colors!\n", 2);
		ft_free(1, data);
	}
}
