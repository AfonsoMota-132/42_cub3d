/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:50:49 by afogonca          #+#    #+#             */
/*   Updated: 2025/04/25 17:08:42 by afogonca         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3d_H
# define CUB3d_H

# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include "../libs/mlx/mlx.h"
/*# include "../libs/libft/libft.h"*/
# include <stdio.h>
# include "../libs/mlx/mlx.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_data {
	t_img	*img;
	void	*mlx;
	void	*win;
	int		win_height;
	int		win_width;
	int		hex_ceiling;
	int		hex_floor;
} t_data;

t_data	*ft_data_init(void);

#endif
