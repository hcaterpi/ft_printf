/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:39:32 by marvin            #+#    #+#             */
/*   Updated: 2019/11/13 15:39:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int   	ft_print_char(char c)
{
	write (1, &c, 1);
    return (1);
}

int     ft_print_number(intmax_t number)
{
	int counter;

	counter = 0;
	if (number == LLONG_MIN)
		counter += ft_print_char('9') + ft_print_number(223372036854775808);
	else
	{
		if (number >= 10)
			counter += ft_print_number(number / 10);
		counter += ft_print_char((number % 10) + '0');
	}
    return (counter);
}

int    ft_print_space(char c, int width)
{
    int  counter;

    counter = 0;
    while (width-- > 0)
        counter += ft_print_char(c);
    return (counter);
}

int	    ft_display(va_list arguments, t_format *specifiers)
{
	char	flag;

	flag = specifiers->type_field;
    if (flag == '%')
        return(ft_print_char(flag));
	else if (flag == 'c')
		return(ft_display_char(arguments, specifiers));
	else if (flag == 's')
		return (ft_display_string(arguments, specifiers));
	else if (flag == 'p')
		return (ft_display_pointer(arguments, specifiers));
	else if (flag == 'd' || flag == 'i')
		return (ft_display_integer(arguments, specifiers));
	else if (flag == 'o')
		return (ft_display_octal(arguments, specifiers));
	else if (flag == 'u')
		return (ft_display_unsigned(arguments, specifiers));
	else if (flag == 'x' || flag == 'X')
		return (ft_display_hexadecimal(arguments, specifiers));
	else if (flag == 'f')
		return (ft_display_float(arguments, specifiers));
	return (0);
}
