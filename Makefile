# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/02 14:10:31 by ageels        #+#    #+#                  #
#    Updated: 2023/02/02 15:33:18 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub
OBJ_DIR = ./obj
CFLAG = -Wall -Werror -Wextra -Wno-incompatible-pointer-types-discards-qualifiers
LFLAG = -framework Cocoa -framework OpenGL -framework IOKit -I . -lglfw3
CC = clang
SRC = src/main.c
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
#Colors:
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m 
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all : libmlx $(NAME)

libmlx :
	cmake -B ./MLX42/build ./MLX42
	$(MAKE) -C ./MLX42/build -j4
	ln -sF MLX42/build/libmlx42.a

obj_folder :
	@mkdir -pv $(OBJ_DIR)

$(NAME): obj_folder $(OBJ)
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ) libmlx42.a $(LFLAG)
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

