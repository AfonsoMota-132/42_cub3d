/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:50:49 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/06 09:33:51 by afogonca         ###   ########.fr       */
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
# include <sys/time.h>
# include <pthread.h>
// # include "../srcs/render/ft_render.h"

# define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803
# define BLOCK 25

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

}			t_img;

typedef struct s_player 
{
	double	x_pos;
	double	y_pos;
	double	y_look;
	double	x_look;
	double	angle;
	int		angle_y;
} t_player;

typedef struct s_ray
{
	double	dirX;
	double	dirY;
	double	posX;
	double	posY;
	double	planeX;
	double	planeY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	int		orien;
	int		texX;
	double	wallX;
	double	step;
	bool	portal_hit;
	bool	portal_see;
	int		count;
	double	rayPosX;
	double	rayPosY;
}	t_ray;

typedef struct s_mov {
	bool	mov_f;
	bool	mov_b;
	bool	mov_l;
	bool	mov_r;
	bool	lookl;
	bool	lookr;
    int		lookml;
	int		lookmr;
	bool	mov;
	bool	look;
	bool	exit;
	bool	exit_main;
	int		jump;
	int		sound;
	double	time_sound;
	int		shoot;
	bool	pause;
} t_mov;

typedef	struct	s_line_improv_render {
	int		*addr;
	int		*tex_addr;
	double	step;
	double	texPos;
	int		hex_ceil;
	int		hex_floor;
	int		img_sl;
	int		tex_sl;
	int		text_y;
	int		drawEnd;
	int		drawStart;
	int		texX;
	t_img	*tex_wall;
	int		height;
	int		width;
	bool	portal_hit;
	int		count;
	int		hit;
} t_line_improv_render;

typedef struct s_frame_pause {
	int	texX;
	int	texY;
	int	color;
}	t_frame_pause;
typedef	struct s_shoot_rc {
	char	enemy;
	int		hit;
	int		is_moving;
	int		max_offset;
	int		spread;
}	t_shoot_rc;

typedef	struct s_tex_enemy {
	t_img					*tex_enemy;
	t_img					*idle1;
}	t_tex_enemy;

typedef	struct s_tex_iddle {
	t_img	*sprite1;
	t_img	*sprite2;
	t_img	*sprite3;
	t_img	*sprite4;
	t_img	*sprite5;
	t_img	*sprite6;
	t_img	*sprite7;
	t_img	*sprite8;
}	t_tex_iddle;

typedef	struct s_tex_nbrs {
	t_img	*nbr_0;
	t_img	*nbr_1;
	t_img	*nbr_2;
	t_img	*nbr_3;
	t_img	*nbr_4;
	t_img	*nbr_5;
	t_img	*nbr_6;
	t_img	*nbr_7;
	t_img	*nbr_8;
	t_img	*nbr_9;
}	t_tex_nbrs;
typedef struct	s_enemy 
{
	t_player		*data;
	char			map;
	bool			render;
	bool			visible;
	t_ray			*ray;
	t_tex_iddle		*tex_iddle;
	t_img			*tex;
	double			next_frame;
	int				frame;
	struct s_data	*rdata;
	struct s_enemy	*next;
} t_enemy;

typedef	struct s_enemy_improv_render {
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteHeight;
	int		drawStartY;
	int		drawEndY;
	int		spriteWidth;
	int		drawStartX;
	int		drawEndX;
	int		texX;
	int		d;
	int		texY;
	int		color;
}	t_enemy_improv_render;

typedef struct s_portal
{
	double	x_pos;
	double	y_pos;
	double	y_look;
	double	x_look;
	int		orien;
	int		angle_y;
} t_portal;

typedef struct s_data 
{
	t_img					*img;
	t_img					*img_player;
	t_img					*img_portal;
	t_img					*img_pause;
	t_img					*tex_pause;
	t_img 					*texture_wall;
	t_img					*tex_north;
	t_img					*tex_south;
	t_img					*tex_east;
	t_img					*tex_west;
	t_img					*tex_pl;
	t_tex_nbrs				*nbrs;
	void					*mlx;
	void					*win;
	t_player				*player;
	t_player				*player1;
	t_portal				*portalL;
	t_ray					*portal_ray;
	t_enemy					*enemy;
	t_enemy					**enemy_arr;
	t_ray					*ray;
	t_mov					*mov;
	char					**map;
	int						hex_ceiling;
	int						hex_floor;
	double					time_frame;
	double					old_frame;
	double					fps;
	int						nbr_threads;
	pthread_t				*thread;
	double					*zbuffer;
	int						width;
	int						height;
	double					frame_time;
	bool					see_portal;
	struct s_thread_data	*tdata;
} t_data;

typedef struct s_thread_data
{
	t_data	*data;
	t_ray	*ray;
	int		start_x;
	int		end_x;
}   t_thread_data;

t_data	*ft_data_init(void);
void	ft_set_img_def(t_img *img);
void	ft_set_image_pixel(t_img *image, int x, int y, int color);
int		get_wall_dir(int side, int stepX, int stepY);
int		key_hook_press(int key, t_data *data);
int		key_hook_relea(int key, t_data *data);
double	ft_get_time_in_ms();
void    ft_free(int exit_flag, t_data *data);
int		ft_frame_render(t_data *data);
void	ft_mov_set_def(t_mov *mov);
void	ft_data_set_def(t_data *data);
void	ft_win_start(t_data *data);
void	ft_start_tex(t_data *data, t_img *img, char *file);
double	ft_add_angle(double angle, double delta);
void	ft_player_lookul(t_player *player, int angle);
void	ft_render(t_data *data);

#endif
