# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/22 14:28:14 by hcaterpi          #+#    #+#              #
#    Updated: 2019/12/22 15:37:04 by hcaterpi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME =	libftprintf.a

SRCS =	display_binary.c \
		display_char.c \
		display_float.c \
		display_hexadec.c \
		display_integer.c \
		display_octal.c \
		display_pointer.c \
		display_string.c \
		display_unsigned.c \
		display.c \
		ft_ftoa.c \
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
