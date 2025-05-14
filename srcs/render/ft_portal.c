/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_portal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:52:58 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/14 10:53:30 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

void *ft_thread_render_portal(void *arg)
{
    t_thread_data *tdata = (t_thread_data *)arg;
    int x = tdata->start_x - 1;

    while (++x < tdata->end_x)
    {
		ft_set_ray_loop(tdata->ray, x, tdata->data);
        ft_ray_dir(tdata->ray);
        ft_dda(tdata->ray, tdata->data);
		tdata->data->zbuffer[x] = tdata->ray->perpWallDist;
        ft_line_height(tdata->ray, tdata->data);
        ft_pre_render_line(tdata->data, tdata->ray, x, -1);
    }
    return (NULL);
}
