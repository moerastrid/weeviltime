# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/02 14:10:31 by ageels        #+#    #+#                  #
#    Updated: 2023/02/03 13:41:42 by mforstho      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub
OBJ_DIR = ./obj
CFLAG = #-Wall -Werror -Wextra
LFLAG = -L libft -framework Cocoa -framework OpenGL -framework IOKit -I . -lglfw3
CC = clang
SRC = src/main.c\
	src/display/background.c\
	src/display/blokje.c\
	src/display/display.c\
	src/parse/parse.c\
	src/raycast/raycast.c\
	src/get_next_line/get_next_line_utils.c\
	src/get_next_line/get_next_line.c\

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
#Colors:
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m 
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

# LIBFT := libft/libft.a

# $(LIBFT) :
# 	$(MAKE) -C $(dir $(LIBFT))

HEADERS := src/get_next_line/get_next_line.h

all : libmlx $(NAME)

libmlx :
	cmake -B ./MLX42/build ./MLX42
	$(MAKE) -C ./MLX42/build -j4
	ln -sF MLX42/build/libmlx42.a

obj_folder :
	@mkdir -pv $(OBJ_DIR)
	@mkdir -pv $(OBJ_DIR)/display
	@mkdir -pv $(OBJ_DIR)/parse
	@mkdir -pv $(OBJ_DIR)/raycast
	@mkdir -pv $(OBJ_DIR)/get_next_line

$(NAME): obj_folder $(OBJ) $(HEADERS)
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ) libft/libft.a libmlx42.a $(LFLAG)
	@printf "$(_SUCCESS) cub ready.\n"
	
obj/%.o : src/%.c
	@$(CC) $(CFLAG) -o $@ -c $^

clean :
	@test -e obj && rm -fr obj || printf "$(_INFO) No objects to clean \n"
	@rm -rf ./MLX42/build

fclean : clean
	@rm -f $(NAME)
	@rm -f libmlx42.a

re : fclean all

.PHONY: all clean fclean re libmlx

