/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:11:18 by palexand          #+#    #+#             */
/*   Updated: 2025/05/24 22:11:21 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static bool	check_spaces(char **matrix)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (matrix[++i])
	{
		j = 0;
		while (matrix[i][j] == ' ')
			j++;
		while (matrix[i][j])
		{
			if (matrix[i][j] == ' ')
				if (matrix[i][j - 1] != '1' && matrix[i][j - 1] != ' '
				&& matrix[i][j + 1] != ' ' && matrix[i][j + 1] != '1'
			&& matrix[i + 1][j] && matrix[i + 1][j] != ' '
			&& matrix[i + 1][j] != '1' && matrix[i - 1]
			&& matrix[i - 1][j] != ' '
			&& matrix[i - 1][j] != '1')
					return (printf("Error\n invalid map spaces"), FALSE);
			j++;
		}
	}
	return (TRUE);
}

static bool	check_map_borders(char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strlen(line) > 1 && line[i] != '1')
		return (FALSE);
	j = ft_strlen(line) - 1;
	while (line[j] == ' ')
		j--;
	if (line[j] != '1')
		return (FALSE);
	if (ft_strlen(line) == 1 && line[i] != '1')
		return (FALSE);
	return (TRUE);
}

static bool	check_map_walls(char **map, size_t i, size_t j)
{
	if (i > 1 && ft_strlen(map[i]) > ft_strlen(map[i + 1])
		&& j >= ft_strlen(map[i - 1]) && map[i][j] && map[i][j] != '1')
		return (FALSE);
	if (i > 0 && map[i + 1] != NULL
		&& ft_strlen(map[i]) > ft_strlen(map[i - 1])
		&& j >= ft_strlen(map[i + 1]) && map[i][j] && map[i][j] != '1')
		return (FALSE);
	if (!map[i][j] || (i == 0 && map[i + 1] == NULL))
		if (map[i][j] != '1' || map[i][j] != ' ')
			return (FALSE);
	return (TRUE);
}

static bool	check_elements(char *map)
{
	size_t	i;

	i = -1;
	while (map[++i])
	{
		if (map[i] == '\n' && map[i + 1] == '\0')
			break ;
		if (map[i] != ' ' && map[i] != '1' && map[i] != '0'
			&& map[i] != 'N' && map[i] != 'S'
			&& map[i] != 'E' && map[i] != 'W')
			return (FALSE);
	}
	return (TRUE);
}

// @brief	Function to parse the map from the data structure
bool	parse_map(char **map)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (check_spaces(map) == FALSE)
		return (printf("Error\nInvalid spaces\n"), FALSE);
	while (map[++i])
	{
		if (check_elements(map[i]) == FALSE)
			return (printf("Error\n invalid map elements\n"), FALSE);
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ')
				j++;
			if (!map[i][j])
				break ;
			if (check_map_borders(map[i]) == FALSE)
				return (printf("Error\n invalid map borders\n"), FALSE);
			if (check_map_walls(map, i, j) == FALSE)
				return (printf("Error\n invalid map walls\n"), FALSE);
			j++;
		}
	}
	return (TRUE);
}


static bool check_line(char *line)
{
	int		i;

	i = 0;
	while (line)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] != '1' && line[i] != '0')
			return (FALSE);
		else if (line[i] == '1' || line[i] == '0')
			return (TRUE);
	}
	return (FALSE);
}

// @brief	Function to check if the map is valid
// @param	data	Pointer to the data structure
// @return	Returns true if the map is valid, false otherwise
int	size_map(char *file, t_data *data)
{
	size_t	fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"),-1);
	i = 0;
	line = get_next_line(fd);
	while (check_line(line) == FALSE)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (check_line(line) == TRUE)
	{		
		i++;
		free(line);
		line = get_next_line(fd);	
	}
	free(line);
	data->map.map = malloc(sizeof(t_map) * i);
	data->map.matrix = malloc(sizeof(t_map) * i);
	return (close(fd), i);
}

static char	*string_copy(char *line)
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

bool	copy_map(t_data *data, char *file)
{
	int		i;
	int		fd;
	char	*line;
	i = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (check_line(line) == FALSE)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (check_line(line) == TRUE)
	{
		data->map.matrix[i] = string_copy(line);
		data->map.map[i] = string_copy(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (i == 0)
		return (printf("Error\nEmpty map\n"), free(line), close(fd), FALSE);
	return (free(line),data->map.map[i] = NULL, data->map.matrix[i] = NULL, close(fd), TRUE);
}
