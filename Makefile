# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 14:40:19 by htrent            #+#    #+#              #
#    Updated: 2019/12/07 15:30:54 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME =	ft_printf.a

SRCS =	display_char.c \
		display_float.c \
		display_hexadecimal.c \
		display_integer.c \
		display_octal.c \
		display_pointer.c \
		display_string.c \
		display_unsigned.c \
		display.c \
		ft_printf.c \
		parsing.c \
		secondary_functions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar rc $(NAME) $^
		ranlib $(NAME)

$(OBJS): %.o : %.c ft_printf.h
		gcc -Wall -Wextra -Werror -c $<

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
