/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:50:49 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 12:59:01 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# include <sys/time.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define PI 3.141592653589793238462643
# define BLOCK 25
# define TRUE 1
# define FALSE 0

# define NORTH 1
# define SOUTH 2
# define WEST 3
# define EAST 4

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		x;
	int		y;
	int		pixel_bits;
	int		size_line;
	int		endian;
}		t_img;

typedef struct s_player
{
	float	x_pos;
	float	y_pos;
	float	y_look;
	float	x_look;
	float	angle;
}	t_player;

typedef struct s_map
{
	int		max_width;
	int		max_height;
	char	**matrix;
	char	**map;
	char	**fmap;
}	t_map;

typedef struct s_map_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		color_f;
	int		color_c;
	int		line_position;
}	t_map_data;

typedef struct s_ray
{
	double	dirx;
	double	diry;
	double	posx;
	double	posy;
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		color;
	int		orien;
	int		texx;
	double	wallx;
	double	step;
}	t_ray;

typedef struct s_mov
{
	bool	mov_f;
	bool	mov_b;
	bool	mov_l;
	bool	mov_r;
	bool	lookl;
	bool	lookr;
	bool	mov;
	bool	exit;
	bool	exit_main;
	int		mouse;
	bool	open;
}	t_mov;

typedef struct s_line_improv_render
{
	int		*addr;
	int		*tex_addr;
	double	step;
	double	texpos;
	int		hex_ceil;
	int		hex_floor;
	int		img_sl;
	int		tex_sl;
	int		text_y;
	int		drawend;
	int		drawstart;
	int		texx;
	t_img	*tex_wall;
	double	door;
	int		hit;
}	t_line_improv_render;

typedef struct s_minimap
{
	double	cos_a;
	double	sin_a;
	double	rad;
	int		height;
	int		width;
	int		angle;
	int		cx;
	int		cy;
	int		dx;
	int		dy;
	int		src_x;
	int		src_y;
}	t_minimap;

typedef struct s_door
{
	int				x_pos;
	int				y_pos;
	double			pos;
	int				open;
	int				last_open;
	bool			seen;
	struct s_door	*next;
}	t_door;

typedef struct s_minimap_utils
{
	int	pos_x;
	int	pos_y;
	int	x;
	int	y;
}	t_minimap_utils;

typedef struct s_data
{
	t_img		*img;
	t_img		*img_minimap;
	t_img		*texture_wall;
	t_img		*tex_north;
	t_img		*tex_south;
	t_img		*tex_east;
	t_img		*tex_west;
	void		*mlx;
	void		*win;
	t_player	*player;
	t_ray		*ray;
	t_mov		*mov;
	t_map		*map;
	int			hex_ceiling;
	int			hex_floor;
	int			minimap_height;
	int			minimap_width;
	int			fd;
	char		*file;
	double		time_frame;
	double		old_frame;
	double		frame_time;
	t_door		*head_door;
	t_map_data	*map_data;
}	t_data;

t_data	*ft_data_init(char *file);
void	ft_set_img_def(t_img *img);
void	ft_set_image_pixel(t_img *image, int x, int y, int color);
int		get_wall_dir(int side, int stepX, int stepY);
int		key_hook_press(int key, t_data *data);
int		key_hook_relea(int key, t_data *data);
double	ft_get_time_in_ms(void);
void	ft_free(int exit_flag, t_data *data);
int		ft_frame_render(t_data *data);
void	ft_init_mov(t_data *data);
void	ft_data_set_def(t_data *data);
void	ft_win_start(t_data *data);
void	ft_start_tex(t_data *data, t_img *img, char *file);
void	free_rgb(char **rgb);
void	ft_free_map(t_map *map);
void	ft_free_map_data(t_data *data);
void	ft_init_player(t_data *data);
void	ft_init_tex_wall(t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	ft_init_doors(t_data *data);
void	ft_free_img(t_data *data);
void	ft_free_doors(t_data *data);
void	ft_init_minimap(t_data *data);
bool	parse_textures(t_data *data);
void	copy_map(t_data *data, char *file);
bool	check_flood(t_data *data);
bool	trim_and_check(t_data *data);
void	rgb_int(t_data *data);
void	parse_cub_file(char *extension, char *file, t_data *data, bool ffree);
char	*duptrim(char **str, bool check, t_data *data);
char	*string_copy(char *line);
bool	check_line(char *line);
void	copy_map_utils(t_data *data, int fd, char *line);
void	free_map(char **line, int i, int fd);

#endif
