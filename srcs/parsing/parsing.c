/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:11:18 by palexand          #+#    #+#             */
/*   Updated: 2025/06/16 09:35:49 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			&& matrix[i - 1][j] != ' ' && matrix[i - 1][j] != '1')
					return (ft_putstr_fd("Error\n invalid map spaces", 2)
						, FALSE);
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
		return (ft_putstr_fd("Error\nInvalid spaces\n", 2), FALSE);
	while (map[++i])
	{
		if (check_elements(map[i]) == FALSE)
			return (ft_putstr_fd("Error\n invalid map elements\n", 2), FALSE);
		j = -1;
		while (map[i][++j])
		{
			while (map[i][j] == ' ')
				j++;
			if (!map[i][j])
				break ;
			if (check_map_borders(map[i]) == FALSE
				|| check_map_walls(map, i, j) == FALSE)
				return (ft_putstr_fd("Error\n invalid map borders/walls\n", 2)
					, FALSE);
		}
	}
	return (TRUE);
}
