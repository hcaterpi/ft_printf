/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:40:39 by marvin            #+#    #+#             */
/*   Updated: 2019/12/04 13:40:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long double	ft_sign(long double number, int *sign, t_format *specifiers)
{
	if (number >= 0 && number != -0.0f && specifiers->flag_plus == 0
	&& specifiers->flag_space == 0)
		*sign = 0;
	else
	{
		if (number == -0.0f)
			*sign = 45;
		else if (number < 0 && (number *= -1))
			*sign = 45;
		else if (specifiers->flag_plus == 1)
			*sign = 43;
		else if (specifiers->flag_space == 1)
			*sign = 32;
	}
	return (number);
}

static char     	*ft_err_str(int error)
{
    char    *str;

    str = (char*)malloc(sizeof(char) * 5);
	if (error == 1)
	{
		str[0] = '-';
		str[1] = 'n';
		str[2] = 'a';
		str[3] = 'n';
		str[4] = '\0';
	}
	else if (error == 2)
	{
		str[0] = 'i';
		str[1] = 'n';
		str[2] = 'f';
		str[3] = '\0';
	}
    return (str);
}

static char			*ft_get_str(va_list arguments, t_format *specifiers, int *sign)
{
	long double		number;
	char			*str;

    if (specifiers->length == 5)
		number = (long double)(va_arg(arguments, long double));
	else
		number = (double)(va_arg(arguments, double));
    number = ft_sign(number, sign, specifiers);
	if (number != number && (specifiers->precision = -1))
		return (ft_err_str(1));
	else if (number != 0 && number * 10 == number
	&& (specifiers->precision = -1))
		return (ft_err_str(2));
	if (specifiers->precision == -1)
		specifiers->precision = 6;
	str = ft_ftoa(number, specifiers);
	return (str);
}

int             	ft_display_float(va_list arguments, t_format *specifiers)
{
    int				counter;
	int				length;
	int				sign;
	char			*str;

    counter = 0;
	str = ft_get_str(arguments, specifiers, &sign);
	length = ft_strlen(str);
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
