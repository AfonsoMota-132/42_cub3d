/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:07:43 by palexand          #+#    #+#             */
/*   Updated: 2025/04/19 21:27:37 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

bool	parse_textures(t_data *data)
{
	char	*line;
	static int i;

	data->fd = open(data->file, O_RDONLY);
	if (data->fd < 0)
		return (false);
	line = get_next_line(data->fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
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
		else if (data->map_data->NO && data->map_data->EA 
		&& data->map_data->SO && data->map_data->WE 
				&& data->map_data->F && data->map_data->C)
				break ;
		data->map_data->line_position++;
		free(line);
		line = get_next_line(data->fd);
	}
	free(line);
	return (close(data->fd), true);
}

char	*trim_and_check_utils(char *str)
{
	char	*tmp;

	tmp = ft_strtrim(str, " \n");\
	free(str);
	return (tmp);
}
void trim_and_check(t_data *data)
{
	if (data->map_data->NO == NULL || data->map_data->EA == NULL
		|| data->map_data->SO == NULL || data->map_data->WE == NULL)
	{
		write(1, "Error\nInvalid texture path\n", 27);
		exit(-1);
	}
	data->map_data->NO = trim_and_check_utils(data->map_data->NO);
	parse_cub_file(".xpm", data->map_data->NO);
	data->map_data->EA = trim_and_check_utils(data->map_data->EA);
	parse_cub_file(".xpm", data->map_data->EA);
	data->map_data->SO = trim_and_check_utils(data->map_data->SO);
	parse_cub_file(".xpm", data->map_data->SO);
	data->map_data->WE = trim_and_check_utils(data->map_data->WE);
	parse_cub_file(".xpm", data->map_data->WE);
	data->map_data->F = trim_and_check_utils(data->map_data->F);
	data->map_data->C = trim_and_check_utils(data->map_data->C);
}

void	rgb_int(t_data *data)
{
	int i;
	int j;
	char **rgb;

	i = 0;
	j = 0;
	if (data->map_data->F)
	{
		rgb = ft_split(data->map_data->F, ',');
		while (rgb[i])
			i++;
		data->map_data->color_f = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
		ft_matrix_free((void **) rgb);
	}
	if (data->map_data->C)
	{
		rgb = ft_split(data->map_data->C, ',');
		while (rgb[j])
			j++;
		data->map_data->color_c = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
		ft_matrix_free((void **) rgb);
	}
}

void parse_cub_file(char *extension, char *file)
{
	int i;
	i = 0;
	while (file[i] != '.' || ft_strrchr(file, '.') != &file[i])
		i++;
	if (ft_strncmp(&file[i], extension, 5) != 0 || i == 0)
	{
		printf("Error\nInvalid file extension\n");
		exit(-1);
	}
}
