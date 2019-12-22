/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:24:56 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 17:49:12 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct	s_format
{
	bool	flag_minus;
	bool	flag_plus;
	bool	flag_space;
	bool	flag_hash;
	bool	flag_zero;
	int		width_field;
	int		precision;
	enum {
		none,
		hh,
		h,
		ll,
		l,
		L
	}		length;
	char	type_field;
}				t_format;

void			ft_parse(const char **format, t_format *specifiers);

int				ft_print_char(char c);
int				ft_print_string(char *s);
int				ft_print_number(uintmax_t number);
int				ft_print_space(char c, int width);

int				ft_display_char(va_list arguments, t_format *specifiers);
int				ft_display_string(va_list arguments, t_format *specifiers);
int				ft_display_pointer(va_list arguments, t_format *specifiers);
int				ft_display_integer(va_list arguments, t_format *specifiers);
int				ft_display_octal(va_list arguments, t_format *specifiers);
int				ft_display_unsigned(va_list arguments, t_format *specifiers);
int				ft_display_hexadec(va_list arguments, t_format *specifiers);
int				ft_display_float(va_list arguments, t_format *specifiers);
int				ft_display_binary(va_list arguments, t_format *specifiers);
int				ft_display(va_list arguments, t_format *specifiers);

int				ft_strlen(const char *s);
int				ft_nonnegative(int number);
char			ft_get_char(int number, char c);
char			*ft_ftoa(long double number, t_format *specifiers);

int				ft_printf(const char *format, ...);

#endif
