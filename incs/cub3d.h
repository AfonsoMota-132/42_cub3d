/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:50:49 by afogonca          #+#    #+#             */
/*   Updated: 2025/04/26 09:52:52 by afogonca         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3d_H
# define CUB3d_H

# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include "../libs/mlx/mlx.h"
# include "../libs/libft/libft.h"
# include <stdio.h>
# include "../libs/mlx/mlx.h"
# include <math.h>
# include <stdbool.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803
# define BLOCK 25

# define NORTH 1
# define SOUTH 2
# define WEST 3
# define EAST 4
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		x;
	int		y;
	int		bpp;
	int		size_line;
	int		endian;

}			t_img;
typedef struct s_player 
{
	float	x_pos;
	float	y_pos;
	float	y_look;
	float	x_look;
} t_player;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	float	angle;
	double	dir_x;
	double	dir_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		hit;

	double	deltadist_x;
	double	deltadist_y;
	int		step_x;
	int		step_y;
	double	perpwalldist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	float	step;
	float	tex_pos;
	int		y;
	
	double	sidedist_x;
	double	sidedist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
}	t_ray;

typedef struct s_data 
{
	t_img		*img;
	void		*mlx;
	void		*win;
	t_player	*player;
	t_ray		*ray;
	char		**map;
	int			**tex_pix;
	int			txt2a;
	int			win_height;
	int			win_width;
	int			hex_ceiling;
	int			hex_floor;
} t_data;

t_data	*ft_data_init(void);
void	ft_set_img_def(t_img *img);
void	set_image_pixel(t_img *image, int x, int y, int color);
int	ft_frame_render(t_data *data);

#endif
