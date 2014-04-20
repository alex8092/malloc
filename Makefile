CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -g3

LDFLAGS = -lft_malloc -L.

NAME = libft_malloc.so

SRCS = 	malloc.c \
		struc.c \
		show.c \
		free.c \
		realloc.c \
		ft_memcpy.c \
		ft_putaddr.c

SRCS_TEST = main.c

OBJS = $(addprefix obj/,$(SRCS:.c=.o))

OBJS_TEST = $(addprefix obj/,$(SRCS_TEST:.c=.o))

all: $(NAME)

test: $(NAME) $(OBJS_TEST)
	$(CC) -o tests/test.bin $(OBJS_TEST) $(LDFLAGS)
	(export DYLD_LIBRARY_PATH=. ; \
	export DYLD_INSERT_LIBRARIES=$(NAME) ; \
	export DYLD_FORCE_FLAT_NAMESPACE=1 ; \
	ls -lRa .)

$(NAME): $(OBJS)
	$(CC) -shared -o $@ $^

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
