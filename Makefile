# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thrivier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/20 13:43:59 by thrivier          #+#    #+#              #
#    Updated: 2014/04/20 18:25:45 by thrivier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -fPIC -g3

LDFLAGS = -lft_malloc -L.



SRCS = 	malloc.c alloc.c range.c check.c free.c realloc.c

SRCS_TEST = main.c

ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

NAME_SHORT = libft_malloc.so

OBJS = $(addprefix obj/,$(SRCS:.c=.o))

OBJS_TEST = $(addprefix obj/,$(SRCS_TEST:.c=.o))

all: $(NAME)

ft_test: $(NAME) $(OBJS_TEST)
	$(CC) -o tests/test.bin $(OBJS_TEST) $(LDFLAGS)
	./tests/test.bin

test: $(NAME) $(OBJS_TEST)
	$(CC) -o tests/test.bin $(OBJS_TEST) $(LDFLAGS)
	(export DYLD_LIBRARY_PATH=. ; \
	export DYLD_INSERT_LIBRARIES=$(NAME_SHORT) ; \
	export DYLD_FORCE_FLAT_NAMESPACE=1 ; \
	./tests/test.bin)

$(NAME): $(OBJS)
	$(CC) -shared -o $@ $^
	rm -f $(NAME_SHORT)
	ln -s $@ $(NAME_SHORT)

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
