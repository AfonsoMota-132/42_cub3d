/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:04:57 by afogonca          #+#    #+#             */
/*   Updated: 2025/06/16 09:35:12 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../incs/cub3d.h"

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
