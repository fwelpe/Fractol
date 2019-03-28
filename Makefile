# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/07 18:13:37 by fwlpe             #+#    #+#              #
#    Updated: 2019/03/28 14:42:21 by fwlpe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
OS = $(shell uname)
CC = gcc
LFT = libft/libft.a
SRCS = main.c
OBJ_DIR = objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
FLAGS = -Wall -Wextra -Werror -g

ifeq ($(OS), Linux)
	LMLX_FLAGS = -lXext -lX11 -lm
	LMLX = minilibx/libmlx_linux.a
else
	LMLX_FLAGS = -framework OpenGL -framework AppKit
	LMLX = minilibx/libmlx_macos.a
endif

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LFT)
	$(CC) $(OBJS) $(LFT) $(LMLX) $(LMLX_FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $^

$(LFT):
	make -C libft/

clean:
	make -C libft/ clean
	rm -f $(OBJS)

fclean:
	make -C libft/ fclean
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all

norm:
	norminette *.c *.h
