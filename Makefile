# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/02 14:10:31 by ageels        #+#    #+#                  #
#    Updated: 2023/02/02 15:04:08 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub
OBJ_DIR = ./obj
CFLAG = -Wall -Werror -Wextra
MLX := MLX42/libmlx42.a
LFLAG = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
CC = clang

SRC = src/main.c\

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
#Colors:
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m 
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all : $(NAME) libmlx42.a

libmlx42.a :
	cmake -B ./MLX42/build ./MLX42
	ln -s MLX42/build/libmlx42.a

obj_folder :
	@mkdir -pv $(OBJ_DIR)

$(NAME): obj_folder $(OBJ)
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LIB)
	@printf "$(_SUCCESS) cub ready.\n"
	
obj/%.o : src/%.c
	@$(CC) $(CFLAG) -o $@ -c $^

clean :
	@test -e obj && rm -fr obj || printf "$(_INFO) No objects to clean \n"

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all bonus libft clean fclean re

