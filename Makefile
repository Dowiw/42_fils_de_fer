# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 16:36:57 by kmonjard          #+#    #+#              #
#    Updated: 2025/09/11 16:36:58 by kmonjard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
C_FLAGS = -Wall -Werror -Wextra

SRC_DIR = ./src
LIBFT = $(SRC_DIR)/libft/libft.a

MLX_DIR = ./mlx
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

C_FILES = main.c
SRC = $(addprefix $(SRC_DIR)/, $(C_FILES))

OBJ = $(SRC:.c=.o)

INCLUDES = ./headers

#  -- Rules start here --
all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(SRC_DIR)/libft/

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(C_FLAGS) -c $< -o $@ -I$(INCLUDES) -I$(MLX_DIR)

clean:
	@make -C ./src/libft clean
	@echo "Deleting object files in fdf..."
	@rm -f $(OBJ)

fclean: clean
	@make -C ./src/libft fclean
	@echo "Deleting all binaries in fdf..."
	@rm -f $(NAME)
	@rm -f $(OBJ)

re: fclean all

.PHONY: all clean fclean re
