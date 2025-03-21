# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 08:54:03 by afogonca          #+#    #+#              #
#    Updated: 2025/01/22 08:59:36 by afogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L ./libs/minilibx-linux -lm -Ilmlx -lXext -lX11
CC = cc
RM = rm -f

OBJS = $(SRCS:.c=.o)
SRCS = srcs/main.c
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
	$(MAKE) -C ./libs/mlx/ fclean
	
re: fclean all
