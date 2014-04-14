CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iinclude

LDFLAGS = -lft_malloc -L.

NAME = libft_malloc.a

SRCS = malloc.c

SRCS_TEST = main.c

OBJS = $(addprefix obj/,$(SRCS:.c=.o))

OBJS_TEST = $(addprefix obj/,$(SRCS_TEST:.c=.o))

all: $(NAME)

test: $(NAME) $(OBJS_TEST)
	$(CC) -o tests/test.bin $(OBJS_TEST) $(LDFLAGS)
	./tests/test.bin

$(NAME): $(OBJS)
	ar rc $@ $^
	ranlib $@

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj/%.o: tests/%.c
	mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
