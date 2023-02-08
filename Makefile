# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/02 14:10:31 by ageels        #+#    #+#                  #
#    Updated: 2023/02/08 20:19:12 by astrid        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub
OBJ_DIR = ./obj
CFLAG = -Wall -Werror -Wextra -fsanitize=address -g
LFLAG = -framework Cocoa -framework OpenGL -framework IOKit -I . -lglfw3
CC = clang
SRC = src/main.c\
	src/display/background.c\
	src/display/blokje.c\
	src/display/display.c\
	src/display/grid.c\
	src/get_next_line/get_next_line_utils.c\
	src/get_next_line/get_next_line.c\
	src/parse/parse.c\
	src/parse/check_map.c\
	src/raycast/raycast.c\
	src/utils/wraps.c\

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
	mkdir -pv $(OBJ_DIR)/display
	mkdir -pv $(OBJ_DIR)/parse
	mkdir -pv $(OBJ_DIR)/raycast
	mkdir -pv $(OBJ_DIR)/get_next_line
	mkdir -pv $(OBJ_DIR)/utils

$(NAME): obj_folder $(OBJ)
	$(CC) $(CFLAG) -o $(NAME) $(OBJ) ./libft/libft.a libmlx42.a $(LFLAG)
	printf "$(_SUCCESS) cub ready.\n"
	
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

.PHONY: all clean fclean re libmlx

