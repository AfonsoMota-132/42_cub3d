# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 08:54:03 by afogonca          #+#    #+#              #
#    Updated: 2025/05/01 16:27:34 by afogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L ./libs/minilibx-linux -lm -Ilmlx -lXext -lX11
CC = cc
RM = rm -f

OBJS = $(SRCS:.c=.o)

RENDER_SRCS = srcs/render/ft_frame_render.c \
			  srcs/render/ft_cast.c

SRCS = srcs/main.c srcs/ft_init.c \
	   $(RENDER_SRCS)
LIBS = ./libs/mlx/libmlx.a ./libs/libft/libft.a

all: deps $(NAME)

deps: mlx libft

libft:
	$(MAKE) -C ./libs/libft/

mlx:
	$(MAKE) -C ./libs/mlx/

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C ./libs/mlx/ clean

fclean: clean
	$(RM) $(NAME)

re: fclean all
