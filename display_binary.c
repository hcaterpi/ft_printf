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

static char         *ft_zero_str(void)
{
    char    *str;

    str = (char*)malloc(sizeof(char) * 2);
    str[0] = '0';
    str[1] = '\0';
    return (str);
}

static char			*ft_itoa_base(intmax_t number, char c)
{
    intmax_t    buffer;
    int         length;
    char        *str;

    if (number == 0)
        return (ft_zero_str());
    length = 0;
    buffer = number;
    while (buffer && ++length)
        buffer /= 2;
    str = (char*)malloc(sizeof(char) * (length + 1));
	str[length] = '\0';
    buffer = number;
    while (buffer)
    {
        str[length - 1] = ft_get_char(buffer % 2, c);
        buffer /= 2;
        length--;
    }
    return (str);
}

static int          ft_sign(intmax_t number, int *sign, t_format *specifiers)
{
	if (number >= 0 && specifiers->flag_plus == 0
	&& specifiers->flag_space == 0)
		*sign = 0;
	else
	{
		if (number < 0 && (number *= -1))
			*sign = 45;
		else if (specifiers->flag_plus == 1)
			*sign = 43;
		else if (specifiers->flag_space == 1)
			*sign = 32;
	}
	return (number);
}

int					ft_display_binary(va_list arguments, t_format *specifiers)
{
    int     	counter;
	int			length;
    int         sign;
    intmax_t	number;
    char		*str;

	counter = 0;
    number = ft_sign(ft_get_number(arguments, specifiers), &sign, specifiers);
	length = ft_strlen((str = ft_itoa_base(number, 'a')));
	if (sign && length++ && specifiers->flag_zero)
			counter += ft_print_char(sign);
	if (specifiers->flag_zero == 1)
        counter += ft_print_space('0', specifiers->width_field - length);
	else if (specifiers->flag_minus == 0)
		counter += ft_print_space(' ', specifiers->width_field - length
		- ft_nonnegative(specifiers->precision - length));
	if (sign && !specifiers->flag_zero)
		counter += ft_print_char(sign);
	counter += ft_print_space('0', specifiers->precision - length);
    counter += ft_print_string(str);
    if (specifiers->flag_minus == 1)
        counter += ft_print_space(' ', specifiers->width_field - length
		- ft_nonnegative(specifiers->precision - length));
    free(str);
    return (counter);
}
