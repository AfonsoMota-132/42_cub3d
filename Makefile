# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 08:54:03 by afogonca          #+#    #+#              #
#    Updated: 2025/06/12 12:07:02 by afogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -g -O3 -Wall -Wextra -Werror
MLXFLAGS = -L ./libs/minilibx-linux -lm -Ilmlx -lXext -lX11
CC = cc
RM = rm -f

OBJS = $(SRCS:.c=.o)

HOOKS = srcs/hooks/key_hook.c

RENDER_SRCS =	srcs/render/ft_frame_render.c \
				srcs/render/ft_render_line.c \
				srcs/render/ft_render_utils.c \
				srcs/render/ft_player_mov.c

INIT =	srcs/init/ft_init.c 
SRCS =	srcs/main.c srcs/ft_free.c \
		srcs/parsing.c srcs/file_parsing.c \
		srcs/flood_fill.c srcs/file_parsing_utils.c \
		$(RENDER_SRCS) $(HOOKS) $(INIT)

LIBS = ./libs/mlx/libmlx.a ./libs/libft/libft.a

all: deps $(NAME)

deps: mlx libft

libft:
	$(MAKE) -C ./libs/libft/

mlx:
	$(MAKE) -C ./libs/mlx/

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) $(MLXFLAGS) -g

clean:
	$(RM) $(OBJS)
	$(MAKE) -C ./libs/mlx/ clean

fclean: clean
	$(RM) $(NAME)

re: fclean all
