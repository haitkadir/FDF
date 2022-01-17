CC = gcc
SRC = main.c fdf_get_data.c fdf_draw.c

compile:
	@$(CC) $(SRC) -L ./libft -lft -L ./get_next_line -lgnl -L. -lmlx -framework OpenGL -framework AppKit -g


all: compile