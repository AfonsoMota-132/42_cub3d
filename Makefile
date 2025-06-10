#======================================================================#
#                     CUB3D - A C++ 3D Game Engine                     #
#======================================================================#

# This file is part of CUB3D.
NAME = cub3D

#------------------------------------------------------------------------------#
#															FILES & PATHS                                	 	 #
#------------------------------------------------------------------------------#

# Source files
INC_PATH = ./incs
LIB_PATH = ./libs
BUILD_PATH = .build
SRCS_PATH = ./srcs
LIBFT_PATH = $(LIB_PATH)/libft
MLX_PATH = $(LIB_PATH)/mlx

# Header files
HEADERS = $(INC_PATH)/cub3d.h

# Source files

SRCS = $(addprefix $(SRCS_PATH)/, \
			 main.c \
			 parsing.c file_parsing.c \
			 init_data.c \
			 flood_fill.c \
			 free.c)
# inputs.c data_ini.c ft_exit.c raycaster.c calculation.c draw.c fps_counter.c textures.c minimap.c)

# Object files
OBJS = $(addprefix $(BUILD_PATH)/, $(notdir $(SRCS:.c=.o)))

# Libraries
LIBS = $(addprefix $(LIB_PATH)/, \
			libft/libft.a \
			mlx/libmlx.a)

#------------------------------------------------------------------------------#
#															COMPILER & FLAGS                                 #
#------------------------------------------------------------------------------#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
AR = ar rcs
SILENT_MAKE = make -s extra

#-----------------------------------------------------------------------------#
#                              RULES                                          #
#-----------------------------------------------------------------------------#

# All
all: deps $(NAME)
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) BUILD COMPLETED $(GREEN)$(BOLD)$(BUILD)$(RESET)"


$(BUILD_PATH)/%.o: $(SRCS_PATH)/%.c $(HEADERS)
	@mkdir -p $(BUILD_PATH)
	@cc $(CFLAGS) -I/usr/include -Iminilibx-linux -o $@ -c $<


${NAME}: ${OBJS} ${LIBS}
	@echo "$(GREEN)$(BOLD)$(BUILD) BUILDING...$(RESET)"
	@${CC} ${CFLAGS} -o $@ $(OBJS) -L$(LIB_PATH)/libft -lft -L$(LIB_PATH)/mlx -lmlx
	@echo "$(GRN)[Cub3d successfully compiled]$(D)"

# $(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS)
# 	@mkdir -p $(BUILD_PATH)
# 	@$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@

deps:
	@if test ! -d "$(LIBFT_PATH)"; then make -s get_libft; \
		else echo "$(GRN)[Libft folder found]$(D)"; fi
	@if test ! -d "$(MLX_PATH)"; then make -s get_minilibx; \
		else echo "$(MAG)[Minilibx folder found]$(D)"; fi
	@echo "$(GREEN)$(BOLD)$(BUILD) INCLUDED HEADERS $(RESET)"
	# @${CC} ${CFLAGS} -I ${INC_PATH} -MD -c $< -o $@
	# @echo "$(GREEN)$(BOLD)$(CHECKMARK) $(NAME) $(GREEN)$(BOLD)$(BUILD)$(RESET)"


get_libft:
	@echo "[$(CYA)Downloading Libft$(D)]"
	git clone git@github.com:PatzCM/Libft_42.git $(LIBFT_PATH)
	@echo "$(CYA)[Libft successfully downloaded]$(D)"

get_minilibx:
	@echo "[$(MAG)Downloading Minilibx$(D)]"
	git clone git@github.com:42Paris/minilibx-linux.git $(MLX_PATH)
	@echo "$(MAG)[Minilibx successfully downloaded]$(D)"


# Build libft
$(LIBFT_PATH)/libft.a:
	@echo "$(GREEN)$(BOLD)Building libft$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH)

# Build mlx
$(LIB_PATH)/mlx/libmlx.a:
	@echo "$(GREEN)$(BOLD)Building mlx$(RESET)"
	@$(MAKE) -C $(LIB_PATH)/mlx

clean:
	@echo "$(RED)$(BOLD)$(CLEAN) CLEANING FILES... $(RESET)"
	@${RM} ${BUILD_PATH}
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) SUCCESS CLEANING! $(GREEN)$(BOLD)$(CLEAN)$(RESET)"

fclean: clean
	@echo "$(RED)$(BOLD)$(CLEAN) REMOVING EXECUTER... $(RESET)"
	@${RM} ${NAME}
	@${RM} ${LIB_PATH}
	@echo "$(BCYA)[fclean] Archive, Libft and Minilibx removed$(D)"
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) SUCCESS REMOVING! $(GREEN)$(BOLD)$(CLEAN)$(RESET)"

re: 
	@echo "$(GREEN)$(BOLD)$(BUILD) REBUILDING !$(RESET)"
	@$(MAKE) -s fclean
	@$(MAKE) -s all

again: clean
	@echo "$(BCYA)[rebuilding...]$(D)"
	@$(RM) $(NAME)
	@$(RM) $(LIB_NAME)
	@$(MAKE) -s


.PHONY: all clean fclean re again

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


