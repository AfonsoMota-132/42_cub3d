/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:31:46 by palexand          #+#    #+#             */
/*   Updated: 2025/06/16 14:09:06 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	flood_fill(t_data *data, int x, int y)
{
	int		line;

	line = 0;
	while (data->map->map[line])
		line++;
	if (x < 0 || x >= line || y < 0 || x >= data->map->max_height - 1
		|| y > (int)(ft_strlen(data->map->map[x]) - 1))
		return (x < data->map->max_height - 1
			&& y < (int)(ft_strlen(data->map->map[x]) - 1)
			&& data->map->map[x][y] == '1');
	if (data->map->map[x][y] == '1' || data->map->map[x][y] == 'X')
		return (TRUE);
	data->map->map[x][y] = 'X';
	if (!flood_fill(data, x + 1, y))
		return (FALSE);
	if (!flood_fill(data, x - 1, y))
		return (FALSE);
	if (!flood_fill(data, x, y + 1))
		return (FALSE);
	if (!flood_fill(data, x, y - 1))
		return (FALSE);
	return (TRUE);
}

int	ft_strchr_player(char *line)
{
	if (ft_strchr(line, 'S'))
		return (ft_strchr_len(line, 'S'));
	if (ft_strchr(line, 'N'))
		return (ft_strchr_len(line, 'N'));
	if (ft_strchr(line, 'E'))
		return (ft_strchr_len(line, 'E'));
	if (ft_strchr(line, 'W'))
		return (ft_strchr_len(line, 'W'));
	return (0);
}

void	find_player(t_data *data)
{
	int	i;
	int	player;

	i = -1;
	player = 0;
	while (data->map->map[++i])
	{
		if (ft_strchr_player(data->map->map[i]))
		{
			data->player->x_pos = i + 0.5;
			data->player->y_pos = ft_strchr_player(data->map->map[i]) + 0.5;
			player++;
		}
	}
	if (player != 1)
	{
		ft_putstr_fd("Error\nMultiple players found\n", 2);
		ft_free(1, data);
	}
}

static bool	check_valid_flood_fill(t_data *data)
{
	int	i;

	i = 0;
	if ((ft_strchr(data->map->map[0], 'X')
			|| ft_strchr(data->map->map[data->map->max_height - 1], 'X')))
		return (FALSE);
	while (data->map->map[i++][0] && i <= data->map->max_height - 1)
		if (data->map->map[i][0] == 'X'
			|| (ft_strlen(data->map->map[i]) > 0
			&& data->map->map[i][ft_strlen(data->map->map[i]) - 1] == 'X'))
			return (FALSE);
	return (TRUE);
}

bool	check_flood(t_data *data)
{
	int		i;
	char	**tmp;

	i = -1;
	data->map->fmap = ft_calloc(sizeof(char *), data->map->max_height + 1);
	while (data->map->map[++i])
		data->map->fmap[i] = ft_strdup(data->map->map[i]);
	data->map->fmap[i] = NULL;
	tmp = data->map->map;
	data->map->map = data->map->fmap;
	if (!flood_fill(data, data->player->x_pos, data->player->y_pos)
		|| !check_valid_flood_fill(data))
	{
		data->map->map = tmp;
		ft_matrix_free((void **) data->map->fmap);
		return (printf("Error\nMap is not closed\n"), FALSE);
	}
	data->map->map = tmp;
	ft_matrix_free((void **) data->map->fmap);
	return (TRUE);
}
