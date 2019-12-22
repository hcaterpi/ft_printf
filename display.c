/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:21:31 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 17:49:13 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_print_string(char *s)
{
	int		counter;

	counter = 0;
	while (*s)
		counter += ft_print_char(*s++);
	return (counter);
}

int		ft_print_number(uintmax_t number)
{
	int		counter;

	counter = 0;
	if (number >= 10)
		counter += ft_print_number(number / 10);
	counter += ft_print_char((number % 10) + '0');
	return (counter);
}

int		ft_print_space(char c, int width)
{
	int		counter;

	counter = 0;
	while (width-- > 0)
		counter += ft_print_char(c);
	return (counter);
}

int		ft_display(va_list arguments, t_format *specifiers)
{
	if (specifiers->type_field == '%')
		return (ft_display_char(arguments, specifiers));
	else if (specifiers->type_field == 'c')
		return (ft_display_char(arguments, specifiers));
	else if (specifiers->type_field == 's')
		return (ft_display_string(arguments, specifiers));
	else if (specifiers->type_field == 'p')
		return (ft_display_pointer(arguments, specifiers));
	else if (specifiers->type_field == 'd' || specifiers->type_field == 'i')
		return (ft_display_integer(arguments, specifiers));
	else if (specifiers->type_field == 'o')
		return (ft_display_octal(arguments, specifiers));
	else if (specifiers->type_field == 'u')
		return (ft_display_unsigned(arguments, specifiers));
	else if (specifiers->type_field == 'x' || specifiers->type_field == 'X')
		return (ft_display_hexadec(arguments, specifiers));
	else if (specifiers->type_field == 'f')
		return (ft_display_float(arguments, specifiers));
	else if (specifiers->type_field == 'b' || specifiers->type_field == 'B')
		return (ft_display_binary(arguments, specifiers));
	return (0);
}
