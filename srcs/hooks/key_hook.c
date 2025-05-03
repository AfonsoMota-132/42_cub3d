/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:23:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/03 12:44:40 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int ft_atleast_point1(double value)
{
    double intpart;
    double fracpart = modf(value, &intpart);
    return (fracpart >= 0.1);
}

int	verify_outofbounds(t_data *data, double x, double y)
{
	if (!ft_atleast_point1(x))
		x = x - 1;
	if (!ft_atleast_point1(y))
		y = y - 1;
	if (data->map[(int)x][(int)y] == 1)
		return (0);
	return (1);
}

double ft_add_angle(double angle, double delta)
{
    angle += delta;
    if (angle >= 360.0)
        angle -= 360.0;
    else if (angle < 0.0)
        angle += 360.0;
    return (angle);
}

int	key_hook_press(int key, t_data *data)
{
	double	next_pos;

	if (key == 65307)
	{
		mlx_do_key_autorepeaton(data->mlx);
		exit(0);
	}
	if (key == 119)
		data->mov->mov_f = true;
	if (key == 97)
		data->mov->mov_l = true;
	if (key == 115)
		data->mov->mov_b = true;
	if (key == 100)
		data->mov->mov_l = true;
	return (0);
}
