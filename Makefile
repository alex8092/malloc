CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iinclude

LDFLAGS = 

NAME = libft_malloc_$(HOSTTYPE).so

SRCS = malloc.c

OBJS = $(addprefix obj/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
