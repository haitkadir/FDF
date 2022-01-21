NAME = libgnl.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = get_next_line.c get_next_line_utils.c
OBJS = $(SRC:%.c=%.o)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

all: $(NAME)

%.o : %.c get_next_line.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -f $(OBJS)
fclean: clean
	@rm -f $(NAME)