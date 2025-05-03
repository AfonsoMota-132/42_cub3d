/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_txt_px.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:09:37 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/02 09:13:17 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	init_texture_pixels(t_data *data)
{
	int	i;

	// if (data->texture_pixels)
	// 	free_tab((void **)data->texture_pixels);
	data->tex_pix = ft_calloc(data->win_height + 1,
			sizeof * data->tex_pix);
	// if (!data->texture_pixels)
	// 	clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	i = 0;
	while (i < data->win_height)
	{
		data->tex_pix[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pix);
		// if (!data->texture_pix[i])
		// 	clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
		i++;
	}
}
