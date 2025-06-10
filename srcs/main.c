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

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data || ac != 2)
		return (write(1, "Error\n", 6), 1);
	init_data(data, av[1]);
	parse_cub_file(".cub", av[1]);
	parse_textures(data);
	trim_and_check(data);
	rgb_int(data);
	copy_map(data, av[1]);
	if (parse_map(data->map.map) == FALSE)
		return (write(1, "Error\n", 6), 1);
	check_flood(data);
	free_data(data);
}
