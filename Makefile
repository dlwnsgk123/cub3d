# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 09:38:37 by junhalee          #+#    #+#              #
#    Updated: 2021/10/08 09:38:37 by junhalee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS =  src/main.c \
		src/parse_map.c \
		src/error.c \
		src/draw_map.c \
		src/move_player.c \

CC = gcc

CFLAGS = -fsanitize=address

LEAKFLAGS = 

OBJ = $(SRCS:.c=.o)

OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	MLX = ./mlx
	HEADER = ./includes/
	MLX_LINK = -L $(MLX) -lmlx -framework OpenGL -framework AppKit
else
	MLX = ./mlx-linux
	HEADER = ./includes_linux/
	MLX_LINK = -L $(MLX) -lmlx -lm -lXext -lX11
endif

LIB_LINK = -L ./Libft -lft

%.o : %.c
	$(CC) $(CFLAGS) -I$(HEADER) -o $@ -c $<

$(NAME) : $(OBJ)
	$(MAKE) -s -C ./Libft all
	$(MAKE) -s -C $(MLX) all
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LINK) $(LIB_LINK) -o $(NAME)

all : $(NAME)

clean:
#	$(MAKE) -s -C ./Libft clean
#	$(MAKE) -s -C $(MLX) clean
	rm -rf $(OBJ)

fclean:
#	$(MAKE) -C ./Libft fclean
#	$(MAKE) -C $(MLX) clean
	rm -rf $(OBJ) $(NAME)

re: fclean all

.PHONY : all bonus clean fclean re