# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 12:09:11 by haitkadi          #+#    #+#              #
#    Updated: 2022/01/21 12:09:24 by haitkadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ./src/fdf_main.c ./src/fdf_get_dimensions.c ./src/fdf_get_data.c \
		./src/fdf_draw.c ./src/fdf_calc_data.c ./src/fdf_htoi.c \
		./src/fdf_check_err.c ./src/fdf_events.c

OBJS = $(SRC:%.c=%.o)
NAME = libfdf.a
LIBFT = -L ./assets/libft -lft
LIBGNL = -L ./assets/gnl -lgnl
LIBFDF = -L. -lfdf

all: $(NAME)
	@make -C ./assets/libft
	@make -C ./assets/gnl
	@echo "\033[0;32m Compiled successfuly"
	@echo "\033[0;32m Usage ./fdf map [optional] [optional]"
	@$(CC) $(CFLAGS) -lm $(LIBFDF) $(LIBFT) $(LIBGNL) \
		-L. -lmlx -framework OpenGL -framework AppKit -o fdf

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o : %.c ./src/fdf.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -f $(OBJS)
	@make clean -C ./assets/libft
	@make clean -C ./assets/gnl
	@echo "\033[0;31m Object files removed"

fclean: clean
	@rm -f $(NAME) fdf
	@make fclean -C ./assets/libft
	@make fclean -C ./assets/gnl
	@echo "\033[0;31m Program and archive file removed"

re: fclean all
