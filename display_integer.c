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
		number = (char)(va_arg(arguments, int));
	else if (specifiers->length == 2)
		number = (short)(va_arg(arguments, int));
	else if (specifiers->length == 3)
		number = (long long)(va_arg(arguments, long long int));
	else if (specifiers->length == 4)
		number = (long)(va_arg(arguments, long int));
	else
		number = (int)(va_arg(arguments, int));
	return (number);
}

static int			ft_numlensign(intmax_t *number, int *sign, t_format *specifiers)
{
	intmax_t	buffer;
	int			digit;

	digit = 1;
	if (*number >= 0 && specifiers->flag_plus == 0 && specifiers->flag_space == 0)
		*sign = 0;
	else
	{
		digit++;
		specifiers->precision++;
		if (*number < 0 && (*number *= -1))
			*sign = 45;
		else if (specifiers->flag_plus == 1)
			*sign = 43;
		else if (specifiers->flag_space == 1)
			*sign = 32;
	}
	if (*number == LLONG_MIN)
		return (20);
	buffer = *number;
	while ((buffer /= 10) > 0)
		digit++;
	return (digit);
}

int					ft_display_integer(va_list arguments, t_format *specifiers)
{
    int     	counter;
	int			length;
    intmax_t	number;
	int			sign;

	counter = 0;
    number = ft_get_number(arguments, specifiers);
    length = ft_numlensign(&number, &sign, specifiers);
	if (sign && specifiers->flag_zero)
			counter += ft_print_char(sign);
	if (specifiers->flag_zero == 1)
        counter += ft_print_space('0', specifiers->width_field - length);
	else if (specifiers->flag_minus == 0)
		counter += ft_print_space(' ', specifiers->width_field - length
		- ft_nonnegative(specifiers->precision - length));
	if (sign && !specifiers->flag_zero)
			counter += ft_print_char(sign);
	counter += ft_print_space('0', specifiers->precision - length);
    counter += ft_print_number(number);
    if (specifiers->flag_minus == 1)
        counter += ft_print_space(' ', specifiers->width_field - length
		- ft_nonnegative(specifiers->precision - length));
    return (counter);
}
