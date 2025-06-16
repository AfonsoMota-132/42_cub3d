/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:02:12 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 12:36:13 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	rgb_values(char **rgb)
{
	int	i;

	i = -1;
	while (rgb[++i])
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (FALSE);
	return (TRUE);
}

char	*duptrim(char **str, bool check, t_data *data)
{
	char	*temp;

	temp = ft_strtrim(*str, " \n");
	if (check)
		parse_cub_file(".xpm", temp, data, TRUE);
	free(*str);
	return (temp);
}

void	rgb_int(t_data *data)
{
	char	**rgb;

	rgb = NULL;
	if (data->map_data->f)
	{
		rgb = ft_split(data->map_data->f, ',');
		data->map_data->color_f = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8
			| ft_atoi(rgb[2]);
	}
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb_values(rgb) == FALSE)
		return (free_rgb(rgb), ft_putstr_fd("Error\nInvalid RGB values\n", 2)
			, ft_free(1, data));
	if (rgb)
		free_rgb(rgb);
	if (data->map_data->c)
	{
		rgb = ft_split(data->map_data->c, ',');
		data->map_data->color_c = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8
			| ft_atoi(rgb[2]);
	}
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb_values(rgb) == FALSE)
		return (free_rgb(rgb), ft_putstr_fd("Error\nInvalid RGB values\n", 2)
			, ft_free(1, data));
	free_rgb(rgb);
}
