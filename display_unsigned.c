/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:13:36 by marvin            #+#    #+#             */
/*   Updated: 2019/11/24 15:13:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t		ft_get_number(va_list arguments, t_format *specifiers)
{
	intmax_t	number;

	if (specifiers->length == 1)
		number = (unsigned char)(va_arg(arguments, unsigned int));
	else if (specifiers->length == 2)
		number = (unsigned short)(va_arg(arguments, unsigned int));
	else if (specifiers->length == 3)
		number = (unsigned long long)(va_arg(arguments, unsigned long long int));
	else if (specifiers->length == 4)
		number = (unsigned long)(va_arg(arguments, unsigned long int));
	else
		number = (unsigned int)(va_arg(arguments, unsigned int));
	return (number);
}

static int			ft_numlen(intmax_t number)
{
	intmax_t	buffer;
	int			digit;

	digit = 1;
	buffer = number;
	while ((buffer /= 10) > 0)
		digit++;
	return (digit);
}

int					ft_display_unsigned(va_list arguments, t_format *specifiers)		// norme
{
    int     	counter;
	int			length;
    intmax_t	number;

	counter = 0;
    number = ft_get_number(arguments, specifiers);
    length = ft_numlen(number);
	if (specifiers->flag_minus == 0)
        counter += ft_print_space(' ', specifiers->width_field - length - ft_nonnegative(specifiers->precision - length));
	counter += ft_print_space('0', specifiers->precision - length);
    counter += ft_print_number(number);
    if (specifiers->flag_minus == 1)
        counter += ft_print_space(' ', specifiers->width_field - length - ft_nonnegative(specifiers->precision - length));
    return (counter);
}
