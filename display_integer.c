/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 14:26:58 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 18:52:43 by hcaterpi         ###   ########.fr       */
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

static int			ft_lensign(intmax_t *number, int *s, t_format *specifiers)
{
	intmax_t	buffer;
	int			digit;

	digit = 1;
	if (*number >= 0 && !(specifiers->flag_plus) && !(specifiers->flag_space))
		*s = 0;
	else
	{
		if (digit++ && specifiers->precision != -1)
			specifiers->precision++;
		if (*number < 0 && (*number *= -1))
			*s = 45;
		else if (specifiers->flag_plus == 1)
			*s = 43;
		else if (specifiers->flag_space == 1)
			*s = 32;
	}
	if (*number == LLONG_MIN)
		return (20);
	buffer = *number;
	while ((buffer /= 10) > 0)
		digit++;
	if (!(*number) && !(specifiers->precision) && !(specifiers->flag_plus))
		digit = 0;
	return (digit);
}

int					ft_display_integer(va_list arguments, t_format *specifiers)
{
	int			counter;
	int			length;
	intmax_t	number;
	int			sign;

	counter = 0;
	number = ft_get_number(arguments, specifiers);
	length = ft_lensign(&number, &sign, specifiers);
	if (sign && specifiers->flag_zero)
		counter += ft_print_char(sign);
	if (specifiers->flag_zero == 1 && specifiers->precision == -1)
		counter += ft_print_space('0', specifiers->width_field - length);
	else if (specifiers->flag_minus == 0)
		counter += ft_print_space(' ', specifiers->width_field - length
		- ft_nonnegative(specifiers->precision - length));
	if (sign && !specifiers->flag_zero)
		counter += ft_print_char(sign);
	counter += ft_print_space('0', specifiers->precision - length);
	if (number || specifiers->precision || specifiers->flag_plus)
		counter += ft_print_number(number);
	if (specifiers->flag_minus == 1)
		counter += ft_print_space(' ', specifiers->width_field - length
		- ft_nonnegative(specifiers->precision - length));
	return (counter);
}
