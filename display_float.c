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

// https://github.com/Eywek/42/blob/master/ft_printf/srcs/types/floats.c
// https://github.com/Eywek/42/blob/master/ft_printf/srcs/utils/floats.c
// https://ravesli.com/urok-33-tip-dannyh-s-plavayushhej-tochkoj-floating-point/

static double	ft_get_number(va_list arguments, t_format *specifiers)
{
	double  number;

	if (specifiers->length == 4)
		number = (double)(va_arg(arguments, double));
    else if (specifiers->length == 5)
		number = (long double)(va_arg(arguments, long double));
	else
		number = (double)(va_arg(arguments, double));
	return (number);
}

double	ft_pow(double n, int pow)
{
	if (pow)
		return (n * ft_pow(n, pow - 1));
	else
		return (1);
}

static double	ft_sign(double number, int *sign, t_format *specifiers)
{
	if (number >= 0 && specifiers->flag_plus == 0 && specifiers->flag_space == 0)
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

static char		*ft_ftoa(double number, t_format *specifiers)
{
	unsigned long	buffer;
	unsigned long	decimal;
    int				length;
    char			*str;

	length = 0;
	if (specifiers->precision > 0)
		length = specifiers->precision + 1;
    buffer = (long)number;
	while (buffer && ++length)
        buffer /= 10;
	str = (char*)malloc(sizeof(char) * (length + 1));
    str[length] = '\0';

	decimal = (unsigned long)((number - (long)number) * ft_pow(10, specifiers->precision + 1));
	if (decimal % 10 > 4)
		decimal = decimal / 10 + 1;
	else
		decimal = decimal / 10;
	while (decimal)
	{
		str[length - 1] = decimal % 10 + '0';
		decimal /= 10;
		length--;
	}
	if (specifiers->precision)
	{
		str[length - 1] = '.';
		length--;
	}

	buffer = (long)number;
	while (buffer)
	{
		str[length - 1] = buffer % 10 + '0';
		buffer /= 10;
		length--;
	}
	return (str);
}

int             ft_display_float(va_list arguments, t_format *specifiers)
{
    int     counter;
	int		length;
    double  number;
	int		sign;
	char	*str;

    counter = 0;
    number = ft_sign(ft_get_number(arguments, specifiers), &sign, specifiers);
	if (specifiers->precision == -1)
		specifiers->precision = 6;
	str = ft_ftoa(number, specifiers);
	length = ft_strlen(str);
	if (sign)
		length++;

	if (specifiers->flag_zero == 1)
	{
		if (sign)
			counter += ft_print_char(sign);
        counter += ft_print_space('0', specifiers->width_field - length);
	}
    else if (specifiers->flag_minus == 0)
	{
        counter += ft_print_space(' ', specifiers->width_field - length - ft_nonnegative(specifiers->precision - length));
		if (sign)
			counter += ft_print_char(sign);
	}
	else if (sign)
		counter += ft_print_char(sign);
	counter += ft_print_space('0', specifiers->precision - length);
	while (*str)
		counter += ft_print_char(*str++);
	if (specifiers->flag_minus == 1)
        counter += ft_print_space(' ', specifiers->width_field - length - ft_nonnegative(specifiers->precision - length));
    //free(trash);
	return (counter);
}
