# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/02 14:10:31 by ageels        #+#    #+#                  #
#    Updated: 2023/03/03 22:08:54 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
OBJ_DIR = ./cub_obj
CFLAG = -Wall -Werror -Wextra -g #-fsanitize=address
IFLAG = -I . -I ./MLX42/include
LFLAG = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
CC = clang

SRC = cub_src/main.c\
	cub_src/debug/print_map.c\
	cub_src/graphics/display_rays.c\
	cub_src/graphics/draw.c\
	cub_src/graphics/gameloop.c\
	cub_src/graphics/graphics.c\
	cub_src/graphics/hooks.c\
	cub_src/graphics/line.c\
	cub_src/parse/check_map.c\
	cub_src/parse/get_data.c\
	cub_src/parse/get_elem.c\
	cub_src/parse/get_map.c\
	cub_src/parse/parse.c\
	cub_src/parse/set_map.c\
	cub_src/raycasting/degree_calc.c\
	cub_src/raycasting/raycasting.c\
	cub_src/utils/frees.c\
	cub_src/utils/get_next_line.c\
	cub_src/utils/libft_extra.c\
	cub_src/utils/single_alloc_split.c\
	cub_src/utils/wraps.c\

ifdef DEBUG
CFLAG += -fsanitize=address -g
endif

OBJ = $(patsubst cub_src/%.c,cub_obj/%.o,$(SRC))
# $(error $(OBJ))
#Colors:
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all : mylibft libmlx $(NAME)

mylibft :
	@make -C ./libft

libmlx :
	cmake -DDEBUG=1 -B ./MLX42/build ./MLX42 
	$(MAKE) -C ./MLX42/build -j4 
	ln -sF MLX42/build/libmlx42.a

obj_folder :
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/debug
	mkdir -p $(OBJ_DIR)/graphics
	mkdir -p $(OBJ_DIR)/parse
	mkdir -p $(OBJ_DIR)/raycasting
	mkdir -p $(OBJ_DIR)/utils

$(NAME): obj_folder $(OBJ)
	$(CC) $(CFLAG) $(IFLAG) -o $(NAME) $(OBJ) ./libft/libft.a libmlx42.a $(LFLAG)
	printf "$(_SUCCESS) cub3D ready.\n"

cub_obj/%.o : cub_src/%.c
	$(CC) $(CFLAG) $(IFLAG) -o $@ -c $<

clean :
	test -e $(OBJ_DIR) && rm -fr $(OBJ_DIR) || printf "$(_INFO) No objects to clean \n"
	rm -rf ./MLX42/build
	make clean -C ./libft

fclean : clean
	rm -f $(NAME)
	rm -f libmlx42.a
	make fclean -C ./libft

re : fclean all

.PHONY: all clean fclean re libmlx
