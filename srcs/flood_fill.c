/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:31:46 by palexand          #+#    #+#             */
/*   Updated: 2025/06/13 11:30:41 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

bool	flood_fill(t_data *data, int x, int y)
{
	int		line;
	bool	ret;

	line = 0;
	ret = TRUE;
	while (data->map->map[line])
		line++;
	if (x < 0 || x >= line || y < 0 || x > data->map->max_height
		|| y >= (int)(ft_strlen(data->map->map[x]) - 1))
	{
		return (x < data->map->max_height
			&& y < (int)(ft_strlen(data->map->map[x]) - 1)
			&& data->map->map[x][y] == '1');
	}
	if (data->map->map[x][y] == '1' || data->map->map[x][y] == 'X')
		return (TRUE);
	data->map->map[x][y] = 'X';
	ret = flood_fill(data, x + 1, y);
	if (ret)
		ret = flood_fill(data, x - 1, y);
	if (ret)
		ret = flood_fill(data, x, y + 1);
	if (ret)
		ret = flood_fill(data, x, y - 1);
	return (ret);
}

static bool	check_valid_flood_fill(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if ((ft_strchr(data->map->map[0], 'X')
			|| ft_strchr(data->map->map[data->map->max_height - 1], 'X')))
		return (FALSE);
	while (data->map->map[i++][0] && i <= data->map->max_height - 1)
	{
		j = ft_strlen(data->map->map[i]) - 1;
		if (data->map->map[i][0] == 'X'
			|| data->map->map[i][ft_strlen(data->map->map[i]) - 1] == 'X')
			return (FALSE);
	}
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
		return (printf("Error\nMap is not closed\n"), FALSE);
	data->map->map = tmp;
	ft_matrix_free((void **) data->map->fmap);
	return (TRUE);
}
