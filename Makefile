# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/02 14:10:31 by ageels        #+#    #+#                  #
#    Updated: 2023/02/28 21:35:52 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
OBJ_DIR = ./cub_obj
CFLAG = -Wall -Werror -Wextra #-fsanitize=address
LFLAG =  -I . -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
CC = clang

SRC = cub_src/main.c\
	cub_src/debug/display_rays.c\
	cub_src/debug/print_map.c\
	cub_src/graphics/background.c\
	cub_src/graphics/gameloop.c\
	cub_src/graphics/line.c\
	cub_src/parse/check_map.c\
	cub_src/parse/get_data.c\
	cub_src/parse/get_elem.c\
	cub_src/parse/get_map.c\
	cub_src/parse/parse.c\
	cub_src/parse/set_map.c\
	cub_src/raycasting/raycasting.c\
	cub_src/utils/frees.c\
	cub_src/utils/get_next_line.c\
	cub_src/utils/libft_extra.c\
	cub_src/utils/single_alloc_split.c\
	cub_src/utils/wraps.c\

ifdef DEBUG
CFLAG += -fsanitize=address -g
endif

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
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
	cmake -B ./MLX42/build ./MLX42
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
	$(CC) $(CFLAG) -o $(NAME) $(OBJ) ./libft/libft.a libmlx42.a $(LFLAG)
	printf "$(_SUCCESS) cub3D ready.\n"

cub_obj/%.o : cub_src/%.c
	$(CC) $(CFLAG) -o $@ -c $^

clean :
	test -e $(OBJ_DIR) && rm -fr $(OBJ_DIR) || printf "$(_INFO) No objects to clean \n"
	rm -rf ./MLX42/build
	make clean -C ./libft

fclean : clean
	rm -f $(NAME)
	rm -f libmlx42.a
	make fclean -C ./libft

re : fclean all

# malloc_test: fclean obj_folder mylibft libmlx $(OBJ)
# 	$(CC) $(CFLAG) -fsanitize=undefined -rdynamic -o malloc_test $(OBJ) ./libft/libft.a ./libmlx42.a $(LFLAG) -L. -lmallocator

.PHONY: all clean fclean re libmlx

