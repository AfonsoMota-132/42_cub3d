# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 08:54:03 by afogonca          #+#    #+#              #
#    Updated: 2025/06/16 11:41:42 by afogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#------------------------------------------------------------------------------#
#															FILES & PATHS                                	 	 #
#------------------------------------------------------------------------------#

NAME = cub3D
# Source files
INC_PATH = ./incs
LIB_PATH = ./libs
# BUILD_PATH = .build
SRCS_PATH = ./srcs
LIBFT_PATH = $(LIB_PATH)/libft
MLX_PATH = $(LIB_PATH)/mlx

# Header files
HEADERS = $(INC_PATH)/cub3d.h

# Source files

RENDER_SRCS =	srcs/render/ft_frame_render.c \
				srcs/render/ft_render_line.c \
				srcs/render/ft_render_utils.c \
				srcs/render/ft_render_utils2.c \
				srcs/render/ft_player_mov.c \
				srcs/render/ft_minimap.c

PARSE_SRCS =	srcs/parsing/parsing.c \
				srcs/parsing/file_parsing.c \
				srcs/parsing/flood_fill.c \
				srcs/parsing/rgb.c \
				srcs/parsing/copy_maps_utils.c \
				srcs/parsing/copy_map.c

INIT =	srcs/init/ft_init.c \
		srcs/init/ft_init_tex_player.c \
		srcs/init/ft_init_doors.c

SRCS =	srcs/main.c srcs/ft_free.c \
		srcs/ft_free_map.c \
		$(PARSE_SRCS) \
		$(RENDER_SRCS) $(HOOKS) $(INIT)

LIBS = ./libs/mlx/libmlx.a ./libs/libft/libft.a

#------------------------------------------------------------------------------#
#															COMPILER & FLAGS                                 #
#------------------------------------------------------------------------------#

CFLAGS = -g -O3
#-Wall -Wextra -Werror
MLXFLAGS = -L ./libs/minilibx-linux -lm -Ilmlx -lXext -lX11
CC = cc
RM = rm -rf
SILENT_MAKE = make -s extra

HOOKS = srcs/hooks/key_hook.c
# OBJS = $(addprefix $(BUILD_PATH)/, $(notdir $(SRCS:.c=.o)))
OBJS = $(SRCS:%.c=%.o)

all: deps $(NAME)
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) BUILD COMPLETED $(GREEN)$(BOLD)$(BUILD)$(RESET)"

%.o: %.c
	@cc $(CFLAGS) -I/usr/include -Iminilibx-linux -o $@ -c $<


deps: 
	@if test ! -d "$(LIBFT_PATH)"; then make -s get_libft; \
		else echo "$(GREEN)$(BOLD)$(CHECKMARK) libft already exists $(GREEN)$(BOLD)$(BUILD)$(RESET)"; fi
	@if test ! -d "$(MLX_PATH)"; then make -s get_mlx; \
		else echo "$(GREEN)$(BOLD)$(CHECKMARK) mlx already exists $(GREEN)$(BOLD)$(BUILD)$(RESET)"; fi

get_libft:
	@echo "[$(CYA)Downloading Libft$(D)]"
	@$(MAKE) -C ./libs/libft/
	@echo "$(CYA)[Libft successfully downloaded]$(D)"

get_mlx:
	@echo "[$(MAG)Downloading Minilibx$(D)]"
	git clone git@github.com:42Paris/minilibx-linux.git $(MLX_PATH)
	@echo "$(MAG)[Minilibx successfully downloaded]$(D)"

$(LIBFT_PATH)/libft.a:
	@echo "$(GREEN)$(BOLD)Building libft$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH)

# Build mlx
$(LIB_PATH)/mlx/libmlx.a:
	@echo "$(GREEN)$(BOLD)Building mlx$(RESET)"
	@$(MAKE) -C $(LIB_PATH)/mlx

$(NAME): $(OBJS) $(LIBS)
	@echo "$(GREEN)$(BOLD)$(BUILD) BUILDING...$(RESET)"
	# $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(NAME) $(MLXFLAGS) -g
	@$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx $(MLXFLAGS)
	@echo "$(GRN)[Cub3d successfully compiled]$(D)"

clean:
	@echo "$(RED)$(BOLD)$(CLEAN) CLEANING FILES... $(RESET)"
	@${RM} ${BUILD_PATH}
	@${RM} ${OBJS}
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) SUCCESS CLEANING! $(GREEN)$(BOLD)$(CLEAN)$(RESET)"

fclean: clean
	@echo "$(RED)$(BOLD)$(CLEAN) REMOVING EXECUTER... $(RESET)"
	@${RM} ${NAME}
	@$(MAKE) -C ./libs/libft fclean --silent
	@echo "$(BCYA)[fclean] Archive, Libft and Minilibx removed$(D)"
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) SUCCESS REMOVING! $(GREEN)$(BOLD)$(CLEAN)$(RESET)"

re:	fclean all 
	@echo "$(GREEN)$(BOLD)$(BUILD) REBUILDING !$(RESET)"

#------------------------------------------------------------------------------#
#															COLORS & STYLES                                	 #
#------------------------------------------------------------------------------#
# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)


# Colors
WHITE		= \033[0;37m
YELLOW		= \033[0;33m
CYAN		= \033[0;36m
GREEN		= \033[0;32m
RED			= \033[0;31m
PURPLE		= \033[0;35m
BLUE		= \033[0;34m
RESET		= \033[0m

# Styles
BOLD		= \033[1m
UNDERLINE	= \033[4m
ITALIC		= \033[3m
REVERSE		= \033[7m
# BOLD UNDERLINE	= \033[1;4m
#
#Emojis

CHECK = ✓
CLEAN = 🧹
BUILD = 🔨
ROCKET = 🚀
BOOK = 📚
SPARKLES = ✨
CHECK = 
CHECKMARK = ✔️
CROSS = ❌

.PHONY: all fclean re clean
