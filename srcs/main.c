/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:48:19 by palexand          #+#    #+#             */
/*   Updated: 2025/06/10 21:39:41 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/cub3d.h"

bool	check_validity(t_data *data);

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data || ac != 2)
		return (printf("Error\nUsage: ./cub3D <file.cub>"), free_data(data), 1);
	init_data(data, av[1]);
	parse_cub_file(".cub", av[1]);
	if (check_validity(data) == FALSE)
		return (free_data(data), 1);
	// parse_textures(data);
	// trim_and_check(data);
	// rgb_int(data);
	// copy_map(data, av[1]);
	// if (parse_map(data->map.map) == FALSE)
	// 	return (write(1, "Error\n", 6), free_data(data), 1);
	// check_flood(data);
	free_data(data);
}

bool	check_validity(t_data *data)
{
if (parse_textures(data) == FALSE || trim_and_check(data) == FALSE)
		return (printf("Error\nInvalid textures"), FALSE);
rgb_int(data);
if (copy_map(data, data->file) == FALSE)
		return (printf("Error\nInvalid map"), FALSE);
if (parse_map(data->map.map) == FALSE)
		return (FALSE);
if (check_flood(data) == FALSE)
		return (FALSE);
return (TRUE);
}
