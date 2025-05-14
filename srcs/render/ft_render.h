/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:18:17 by afogonca          #+#    #+#             */
/*   Updated: 2025/05/04 13:18:20 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RENDER_H
# define FT_RENDER_H

# include "../../incs/cub3d.h"

void	ft_player_mov(t_data *data);
void	ft_player_rot(t_data *data);
void	ft_pre_render_line(t_data *data, t_ray *ray, int x);
void	ft_ray_render_line(t_ray *ray, t_data *data);
// void	ft_render_line(int x, int y, t_line_improv_render *line);
void	ft_line_height(t_ray *ray, t_data *data);
int		ft_frame_render(t_data *data);
void	ft_dda(t_ray *ray, t_data *data);
void	ft_dda_enemy(t_ray *ray, t_data *data, char detect);
void	ft_pre_render_loop(t_ray *ray, t_player *player);
void	ft_set_ray_loop(t_ray *ray, int x, t_data *data);
void	ft_ray_dir(t_ray *ray);
double	ft_add_angle(double angle, double delta);
void	ft_player_mov_fb(t_data *data);
void	ft_player_mov_lr(t_data *data);
int		ft_ver_col(char **map, double tempx, double tempy, char execpt);
void	ft_player_lookul(t_player *player, int angle);
double	ft_add_angle(double angle, double delta);
void	ft_render(t_data *data);

#endif
