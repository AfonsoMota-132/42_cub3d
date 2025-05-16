/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:18:17 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/16 11:55:16 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RENDER_H
# define FT_RENDER_H

# include "../../incs/cub3d.h"

void	ft_player_mov(t_data *data);
void	ft_player_rot(t_data *data);
void	ft_pre_render_line(t_data *data, t_ray *ray, int x, int option);
void	ft_ray_render_line(t_ray *ray, t_data *data);
void	ft_line_height(t_ray *ray, t_data *data);
int		ft_frame_render(t_data *data);
void	ft_dda(t_ray *ray, t_data *data, int rec);
void	ft_dda_enemy(t_ray *ray, t_data *data, char detect);
void	ft_pre_render_loop(t_ray *ray, t_player *player);
void	ft_set_ray_loop(t_ray *ray, int x, t_data *data);
void	ft_ray_dir(t_ray *ray);
double	ft_add_angle(double angle, double delta);
void	ft_player_mov_f(t_data *data);
void	ft_player_mov_b(t_data *data);
void	ft_player_mov_l(t_data *data);
void	ft_player_mov_r(t_data *data);
int		ft_ver_col(char **map, double tempx, double tempy, char execpt);
void	ft_player_lookul(t_player *player, int angle);
double	ft_add_angle(double angle, double delta);
void	ft_render(t_data *data);
void	ft_render_portal(t_thread_data *tdata, int x, int end, int rec);
void	ft_render_enemy_sprite(t_enemy_improv_render *edata, \
			t_enemy *enemy, t_data *data);
char	ft_dda_enemy2(t_ray *ray, t_data *data, char detect);
void	ft_load_edata(t_data *data, t_ray *ray, \
				t_enemy_improv_render *edata);
void	ft_pre_render_enemy_sprite(t_data *data, t_ray *ray, t_enemy *enemy);
void	ft_put_fps(t_data *data);
int		ft_pixel_darken(int color, double factor);
void	ft_frame_render_pause_utils(t_data *data);
void	*ft_thread_render(void *arg);
char	ft_dda_shoot(t_ray *ray, t_data *data);
void	ft_shoot_raycasting2(t_data *data, t_shoot_rc *sdata);
void	ft_sort_enemies(t_data *data);
void	*ft_enemy_render_threads(void *arg);
double	ft_calc_dist_sq(t_data *data, t_enemy *enemy);
void	ft_raycasting_enemies_utils2(t_data *data, t_enemy *enemy, \
				int x, int first_x);
void	ft_raycasting_enemies_utils3(t_data *data, t_enemy *enemy);
void	ft_dda_enemies(t_ray *ray, t_data *data);
void	ft_player_mov_utils(t_data *data);
void	ft_set_ray_loop_portal(t_ray *ray, int x, t_data *data);
void	ft_pre_render_loop_portal(t_ray *ray, t_portal *portal);
void	ft_render_line_portal(int x, t_line_improv_render *line, \
			t_data *data, t_ray *ray);

#endif
