/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:07:43 by palexand          #+#    #+#             */
/*   Updated: 2025/06/10 22:07:09 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static bool	check_textures(t_data *data)
{
	if (data->map_data.NO && data->map_data.EA
		&& data->map_data.SO && data->map_data.WE
		&& data->map_data.F && data->map_data.C
		&& ft_strlen(data->map_data.NO) > 1
		&& ft_strlen(data->map_data.SO) > 1
		&& ft_strlen(data->map_data.EA) > 1
		&& ft_strlen(data->map_data.WE) > 1)
		return (TRUE);
	return (FALSE);
}


static bool util_texture(t_data *data, char *line, int i)
{
	if (ft_strnstr(line, "NO", 2 + i))
			data->map_data.NO = ft_strdup(line + (3 + i));
	else if (ft_strnstr(line, "SO", 2 + i))
		data->map_data.SO = ft_strdup(line + 3 + i);
	else if (ft_strnstr(line, "WE", 2 + i))
		data->map_data.WE = ft_strdup(line + 3 + i);
	else if (ft_strnstr(line, "EA", 2 + i))
		data->map_data.EA = ft_strdup(line + 3 + i);
	else if (ft_strnstr(line, "F", 1 + i))
		data->map_data.F = ft_strdup(line + 2 + i);
	else if (ft_strnstr(line, "C", 1 + i))
		data->map_data.C = ft_strdup(line + 2 + i);
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
		data->map_data.line_position++;
		free(line);
		line = get_next_line(data->fd);
	}
	return (free(line), close(data->fd), true);
}

char *duptrim(char *str, bool check)
{
	char *temp;
	temp = ft_strtrim(str, " \n");
	free(str);
	if (check)
		parse_cub_file(".xpm", temp);
	return (temp);
}

bool	trim_and_check(t_data *data)
{
	if (data->map_data.NO == NULL || data->map_data.EA == NULL
		|| data->map_data.SO == NULL || data->map_data.WE == NULL)
		return(printf("Error\nInvalid texture path"), FALSE);
	data->map_data.NO = duptrim(data->map_data.NO, TRUE);
	data->map_data.EA = duptrim(data->map_data.EA, TRUE);
	data->map_data.SO = duptrim(data->map_data.SO, TRUE); 
	data->map_data.WE = duptrim(data->map_data.WE, TRUE);
	data->map_data.F = duptrim(data->map_data.F, FALSE);
	data->map_data.C = duptrim(data->map_data.C, FALSE);
	return (TRUE);
}
static bool rgb_values(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return(FALSE);
		i++;
	}
	return (TRUE);
}

void	rgb_int(t_data *data)
{
	int		i;
	char	**rgb;

	i = -1;
	rgb = NULL;
	if (data->map_data.F)
	{
		rgb = ft_split(data->map_data.F, ',');
		data->map_data.color_f = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8
			| ft_atoi(rgb[2]);
	}
  if (rgb)
		free_rgb(rgb);
	if (data->map_data.C)
	{
		rgb = ft_split(data->map_data.C, ',');
		data->map_data.color_c = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8
			| ft_atoi(rgb[2]);
	}
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb_values(rgb) == FALSE)
		return(free_rgb(rgb), printf("Error\nInvalid RGB values\n"), exit(-1));	
	free_rgb(rgb);
}

void	parse_cub_file(char *extension, char *file)
{
	int	i;

	i = 0;
	if (!file || !ft_strchr(file, '.'))
	{
		printf("Error\nInvalid texture");
		exit(-1);
	}
	while (file[i] != '.' || ft_strrchr(file, '.') != &file[i])
		i++;
	if (ft_strncmp(&file[i], extension, 5) != 0 || i == 0)
	{
		printf("Error\nInvalid file extension\n");
		exit(-1);
	}
}
