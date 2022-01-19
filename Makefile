CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c fdf_get_dimensions.c fdf_get_data.c fdf_draw.c fdf_calc_data.c fdf_htoi.c fdf_check_err.c fdf_keys.c

compile:
	@$(CC) $(CFLAGS) $(SRC) -L ./libft -lft -L ./get_next_line -lgnl -L. -lmlx -framework OpenGL -framework AppKit -g


all: compile