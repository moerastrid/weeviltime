# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/02 14:10:31 by ageels        #+#    #+#                  #
#    Updated: 2023/02/16 21:46:34 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
OBJ_DIR = ./obj
CFLAG = -Wall -Werror -Wextra #-fsanitize=address -g
LFLAG =  -I . -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
CC = clang
SRC = src/main.c\
	src/debug/print_map.c\
	src/display/display_background.c\
	src/display/display_blokje.c\
	src/display/display_walls.c\
	src/display/display.c\
	src/parse/check_map.c\
	src/parse/check_player_spawn.c\
	src/parse/convert_map.c\
	src/parse/init_map.c\
	src/parse/init_plane.c\
	src/parse/init_walls.c\
	src/parse/setup.c\
	src/parse/save_map.c\
	src/utils/get_next_line.c\
	src/utils/math.c\
	src/utils/single_alloc_split.c\
	src/utils/wraps.c\
	src/utils/clean.c\

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
	mkdir -pv $(OBJ_DIR)
	mkdir -pv $(OBJ_DIR)/debug
	mkdir -pv $(OBJ_DIR)/display
	mkdir -pv $(OBJ_DIR)/parse
	mkdir -pv $(OBJ_DIR)/player
	mkdir -pv $(OBJ_DIR)/raycast
	mkdir -pv $(OBJ_DIR)/utils

$(NAME): obj_folder $(OBJ)
	$(CC) $(CFLAG) -o $(NAME) $(OBJ) ./libft/libft.a libmlx42.a $(LFLAG)
	printf "$(_SUCCESS) cub3D ready.\n"
	
obj/%.o : src/%.c
	$(CC) $(CFLAG) -o $@ -c $^

clean :
	test -e obj && rm -fr obj || printf "$(_INFO) No objects to clean \n"
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

