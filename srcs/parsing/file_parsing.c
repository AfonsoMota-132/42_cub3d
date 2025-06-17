/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:07:43 by palexand          #+#    #+#             */
/*   Updated: 2025/06/16 13:03:59 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	check_textures(t_data *data)
{
	if (data->map_data->no && data->map_data->ea
		&& data->map_data->so && data->map_data->we
		&& data->map_data->f && data->map_data->c
		&& ft_strlen(data->map_data->no) > 1
		&& ft_strlen(data->map_data->so) > 1
		&& ft_strlen(data->map_data->ea) > 1
		&& ft_strlen(data->map_data->we) > 1)
		return (TRUE);
	return (FALSE);
}

// static void	util_texture_utils(t_data *data, char *line, int i)
// {
//
// }
static bool	util_texture(t_data *data, char *line, int i)
{
	if (!data->map_data->no && ft_strnstr(line, "NO", 2 + i))
		data->map_data->no = ft_strdup(line + (3 + i));
	else if (!data->map_data->so && ft_strnstr(line, "SO", 2 + i))
		data->map_data->so = ft_strdup(line + 3 + i);
	else if (!data->map_data->we && ft_strnstr(line, "WE", 2 + i))
		data->map_data->we = ft_strdup(line + 3 + i);
	else if (!data->map_data->ea && ft_strnstr(line, "EA", 2 + i))
		data->map_data->ea = ft_strdup(line + 3 + i);
	else if (!data->map_data->f && ft_strnstr(line, "F", 1 + i))
		data->map_data->f = ft_strdup(line + 2 + i);
	else if (!data->map_data->c && ft_strnstr(line, "C", 1 + i))
		data->map_data->c = ft_strdup(line + 2 + i);
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
	if (data->map_data->no == NULL || data->map_data->ea == NULL
		|| data->map_data->so == NULL || data->map_data->we == NULL)
		return (ft_putstr_fd("Error\nInvalid texture path\n", 2)
			, ft_free(1, data), FALSE);
	data->map_data->no = duptrim(&data->map_data->no, TRUE, data);
	data->map_data->ea = duptrim(&data->map_data->ea, TRUE, data);
	data->map_data->so = duptrim(&data->map_data->so, TRUE, data);
	data->map_data->we = duptrim(&data->map_data->we, TRUE, data);
	data->map_data->f = duptrim(&data->map_data->f, FALSE, data);
	data->map_data->c = duptrim(&data->map_data->c, FALSE, data);
	return (TRUE);
}

void	parse_cub_file(char *extension, char *file, t_data *data, bool ffree)
{
	int	i;

	i = 0;
	if (!file || !ft_strchr(file, '.'))
	{
		ft_putstr_fd("Error\nInvalid file\n", 2);
		if (file && ffree)
			free(file);
		ft_free(1, data);
	}
	while (file[i] != '.' || ft_strrchr(file, '.') != &file[i])
		i++;
	if (ft_strncmp(&file[i], extension, 5) != 0 || i == 0 || (ft_strlen(&file[i]) == 4 && file[i - 1] == '/'))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		if (file && ffree)
			free(file);
		ft_free(1, data);
	}
}
