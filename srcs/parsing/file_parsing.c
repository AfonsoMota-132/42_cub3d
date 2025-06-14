/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:07:43 by palexand          #+#    #+#             */
/*   Updated: 2025/06/14 15:03:29 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	check_textures(t_data *data)
{
	if (data->map_data->NO && data->map_data->EA
		&& data->map_data->SO && data->map_data->WE
		&& data->map_data->F && data->map_data->C
		&& ft_strlen(data->map_data->NO) > 1
		&& ft_strlen(data->map_data->SO) > 1
		&& ft_strlen(data->map_data->EA) > 1
		&& ft_strlen(data->map_data->WE) > 1)
		return (TRUE);
	return (FALSE);
}

static bool	util_texture(t_data *data, char *line, int i)
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
	else if (check_textures(data) == TRUE)
		return (TRUE);
	return (FALSE);
}

bool	parse_textures(t_data *data)
{
	char		*line;
	static int	i;

	data->fd = open(data->file, O_RDONLY);
	line = get_next_line(data->fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		if (util_texture(data, line, i) == TRUE)
			break ;
		data->map_data->line_position++;
		free(line);
		line = get_next_line(data->fd);
	}
	while (line)
	{
		free(line);
		line = get_next_line(data->fd);
	}
	return (close(data->fd), true);
}

bool	trim_and_check(t_data *data)
{
	if (data->map_data->NO == NULL || data->map_data->EA == NULL
		|| data->map_data->SO == NULL || data->map_data->WE == NULL)
		return (printf("Error\nInvalid texture path\n")
			, ft_free(1, data), FALSE);
	data->map_data->NO = duptrim(&data->map_data->NO, TRUE, data);
	data->map_data->EA = duptrim(&data->map_data->EA, TRUE, data);
	data->map_data->SO = duptrim(&data->map_data->SO, TRUE, data);
	data->map_data->WE = duptrim(&data->map_data->WE, TRUE, data);
	data->map_data->F = duptrim(&data->map_data->F, FALSE, data);
	data->map_data->C = duptrim(&data->map_data->C, FALSE, data);
	return (TRUE);
}

void	parse_cub_file(char *extension, char *file, t_data *data, bool ffree)
{
	int	i;

	i = 0;
	if (!file || !ft_strchr(file, '.'))
	{
		printf("Error\nInvalid texture\n");
		if (file && ffree)
			free(file);
		ft_free(1, data);
	}
	while (file[i] != '.' || ft_strrchr(file, '.') != &file[i])
		i++;
	if (ft_strncmp(&file[i], extension, 5) != 0 || i == 0)
	{
		printf("Error\nInvalid file extension\n");
		if (file && ffree)
			free(file);
		ft_free(1, data);
	}
}
