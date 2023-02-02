# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/02 14:10:31 by ageels        #+#    #+#                  #
#    Updated: 2023/02/02 14:51:06 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub
OBJ_DIR = ./obj
CFLAG = -Wall -Werror -Wextra
LFLAG = libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
CC = clang

SRC = src/main.c\

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
#Colors:
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all : $(NAME)

obj_folder :
	@mkdir -pv $(OBJ_DIR)

libmlx42.a :
	make -C MLX42/
	ln -s MLX42/libmlx42.a

$(NAME): obj_folder $(OBJ)
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG)
	@printf "$(_SUCCESS) cub ready.\n"
	
obj/%.o : src/%.c
	@$(CC) $(CFLAG) -o $@ -c $^

clean :
	@test -e obj && rm -fr obj || printf "$(_INFO) No objects to clean \n"

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all bonus libft clean fclean re

