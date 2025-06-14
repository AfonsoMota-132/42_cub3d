/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:31:46 by palexand          #+#    #+#             */
/*   Updated: 2025/06/04 18:36:54 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	flood_fill(t_data *data, int x, int y)
{
	int	line;

	line = 0;
	while (data->map.map[line])
		line++;
	if (x < 0 || x >= line || y < 0
		|| y >= data->map.map[x][ft_strlen(data->map.map[x]) - 1])
		return ;
	if (data->map.map[x][y] == '1' || data->map.map[x][y] == 'X')
		return ;
	data->map.map[x][y] = 'X';
	flood_fill(data, x + 1, y);
	flood_fill(data, x - 1, y);
	flood_fill(data, x, y + 1);
	flood_fill(data, x, y - 1);
}

void	find_player(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.map[++i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'S' ||
				data->map.map[i][j] == 'N' ||
				data->map.map[i][j] == 'E' ||
				data->map.map[i][j] == 'W')
			{
				data->player.x = i;
				data->player.y = j;
				data->player_count++;
			}
			j++;
		}
	}
	if (data->player_count == 1)
		return ;
	else
		printf("Error\nMultiple players found\n"), exit(-1);
}

static bool	check_valid_flood_fill(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if ((ft_strchr(data->map.map[0], 'X')
			|| ft_strchr(data->map.map[data->map.max_height - 1], 'X')))
		return (FALSE);
	while (data->map.map[i++][0] && i <= data->map.max_height - 1)
	{
		j = ft_strlen(data->map.map[i]) - 1;
		if (data->map.map[i][0] == 'X'
			|| data->map.map[i][ft_strlen(data->map.map[i]) - 1] == 'X')
			return (FALSE);
	}
	return (TRUE);
}

bool	check_flood(t_data *data)
{
	find_player(data);
	flood_fill(data, data->player.x, data->player.y);
	if (!check_valid_flood_fill(data))
		return (printf("Error\nMap is not closed\n"), FALSE);
	return (TRUE);
}
