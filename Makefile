# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/07 18:13:37 by fwlpe             #+#    #+#              #
#    Updated: 2019/04/07 12:52:20 by cdenys-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
OS = $(shell uname)
CC = gcc
LFT_DIR = libft/
LFT = $(addprefix $(LFT_DIR), libft.a)
SRCS = main.c hooks.c image.c draw.c opencl.c start.c
OBJ_DIR = objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

ifeq ($(OS), Linux)
	LMLX_FLAGS = -lXext -lX11 -lm
	LMLX_DIR = /dev/null
	LMLX = minilibx/libmlx.a
	FLAGS = -g -I defines/linux/ -I /opt/AMDAPPSDK-3.0/include/
	OCL = /opt/AMDAPPSDK-3.0/lib/x86_64/sdk/libamdocl64.so
else
	LMLX_FLAGS = -framework OpenGL -framework AppKit
	LMLX_DIR = minilibx_macos/
	LMLX = $(addprefix $(LMLX_DIR), libmlx.a)
	FLAGS = -Wall -Wextra -Werror -g -I defines/mac/
	OCL = -framework OpenCL
endif

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LFT) $(LMLX)
	$(CC) $(OBJS) $(LFT) $(LMLX) $(LMLX_FLAGS) $(OCL) $(FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $^

$(LFT):
	make -C $(LFT_DIR)

$(LMLX):
	make -C $(LMLX_DIR) || true

clean:
	make -C $(LFT_DIR) clean
	make -C $(LMLX_DIR) clean || true
	rm -f $(OBJS)

fclean:
	make -C $(LFT_DIR) fclean
	make -C $(LMLX_DIR) clean || true
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all

norm:
	norminette *.c *.h
