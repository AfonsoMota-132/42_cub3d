# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 08:54:03 by afogonca          #+#    #+#              #
#    Updated: 2025/04/25 17:05:35 by afogonca         ###   ########.pt        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L ./libs/minilibx-linux -lm -Ilmlx -lXext -lX11
CC = cc
RM = rm -f

OBJS = $(SRCS:.c=.o)
SRCS = srcs/main.c srcs/ft_init.c
LIBS = ./libs/mlx/libmlx.a

all: mlx $(NAME)

mlx:
	@$(MAKE) -C ./libs/mlx/

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C ./libs/mlx/ clean

fclean: clean
	$(RM) $(NAME)

re: fclean all
