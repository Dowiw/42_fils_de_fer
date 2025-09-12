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

NAME=fdf

COMPILE=gcc your_file.c -I./minilibx-linux -L./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd
