/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:30:30 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/12 12:42:17 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static bool	check_spaces(char **matrix)
{
	int	i;
	int	j;

	i = -1;
	while (matrix[++i])
	{
		j = 0;
		while (matrix[i][j] == ' ')
			j++;
		while (matrix[i][j])
		{
			if (matrix[i][j] == ' ')
				if (matrix[i][j - 1] != '1' && matrix[i][j] - 1 != ' '
				&& matrix[i][j + 1] && matrix[i][j + 1] != ' '
				&& matrix[i][j + 1] != '1'
				&& matrix[i + 1][j] && matrix[i + 1][j] != ' '
				&& matrix[i + 1][j] != '1'
				&& matrix[i - 1] && matrix[i - 1][j] != ' '
				&& matrix[i - 1][j] != '1')
					return (printf("Error\n invalid map spaces"), FALSE);
			j++;
		}
	}
	return (TRUE);
}

void	free_map(char **line, int i, int fd)
{
	if (i)
		free(*line);
	*line = get_next_line(fd);
}

bool	parse_map(t_data *data)
{
	int	row;
	int	col;

	row = -1;
	col = -1;
	if (check_spaces(data->map->matrix) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	size_map(char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	i = -2;
	line = get_next_line(fd);
	i++;
	while (line)
	{
		free_map(&line, 1, fd);
		i++;
	}
	return (close(fd), i);
}

void	copy_map(t_data *data, char *file)
{
	int		i;
	int		fd;
	char	*line;

	i = (size_map(file) - data->map_data->line_position);
	data->map->max_height = i;
	if (i > 0)
	{
		fd = open(file, O_RDONLY);
		data->map->map = ft_calloc(sizeof(t_map), i);
		data->map->matrix = ft_calloc(sizeof(t_map), i);
		i = -1;
		while (i++ <= data->map_data->line_position)
			free_map(&line, i, fd);
		while (line && !ft_strchr(line, '1'))
			free_map(&line, 1, fd);
		if (!line)
		{
			ft_putstr_fd("Error!\nNo valid Map!\n", 1);
			ft_free(1, data);
		}
		i = -1;
		while (line)
		{
			data->map->map[++i] = ft_strdup(line);
			data->map->matrix[i] = ft_strdup(line);
			free_map(&line, 1, fd);
		}
		data->map->map[++i] = NULL;
		data->map->matrix[i] = NULL;
		close(fd);
	}
	else
	{
		ft_putstr_fd("Error!\nNo valid Map/map after textures/colors!\n", 1);
		ft_free(1, data);
	}
}
