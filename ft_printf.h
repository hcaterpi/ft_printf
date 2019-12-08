/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:40:45 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/07 21:19:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// https://www.viva64.com/ru/t/0098/
// https://medium.com/@zhang.yine/ft-printf-d95747b7aa5a
// http://c-faq.com/~scs/cgi-bin/faqcat.cgi?sec=varargs
// http://phix.x10.mx/docs/html/printf.htm
// https://github.com/davhojt/ft_printf
// https://github.com/roblabla42/ft_printf
// http://www.cplusplus.com/reference/cstdio/printf/

// non-printable https://github.com/mikim42/ft_printf/blob/master/srcs/print_non_printable.c
// random https://stackoverflow.com/questions/4768180/rand-implementation
//        https://en.wikipedia.org/wiki/Linear_congruential_generator
// binary https://github.com/Eywek/42/blob/master/ft_printf/srcs/types/binary.c

# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>        // uintmax_t
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <wchar.h>         // wint_t

typedef struct      s_format
{
    bool    flag_minus;
    bool    flag_plus;
    bool    flag_space;
    bool    flag_hash;
    bool    flag_zero;
    int     width_field;
    int     precision;
    enum {
        none,
        hh,
        h,
        ll,
        l,
        L
    }       length;
    char    type_field;
}                   t_format;

void	ft_parse(const char **format, t_format *specifiers);

int     ft_print_char(char c);
int     ft_print_number(intmax_t number);
int     ft_print_space(char c, int width);

int     ft_display_char(va_list arguments, t_format *specifiers);
int     ft_display_string(va_list arguments, t_format *specifiers);
int     ft_display_pointer(va_list arguments, t_format *specifiers);
int     ft_display_integer(va_list arguments, t_format *specifiers);
int     ft_display_octal(va_list arguments, t_format *specifiers);
int		ft_display_unsigned(va_list arguments, t_format *specifiers);
int     ft_display_hexadecimal(va_list arguments, t_format *specifiers);
int     ft_display_float(va_list arguments, t_format *specifiers);
int     ft_display(va_list arguments, t_format *specifiers);

int     ft_strlen(const char *s);
int		ft_nonnegative(int number);
char    ft_get_char(int number, char c);

int     ft_printf(const char *format, ...);

#endif
