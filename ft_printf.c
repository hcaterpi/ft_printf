/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:24:41 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 15:24:45 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_init(t_format *specifiers)
{
	specifiers->flag_minus = 0;
	specifiers->flag_plus = 0;
	specifiers->flag_space = 0;
	specifiers->flag_hash = 0;
	specifiers->flag_zero = 0;
	specifiers->width_field = 0;
	specifiers->precision = -1;
	specifiers->length = none;
	specifiers->type_field = 0;
}

int				ft_printf(const char *format, ...)
{
	int			counter;
	t_format	specifiers;
	va_list		arguments;

	counter = 0;
	va_start(arguments, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ft_init(&specifiers);
			ft_parse(&format, &specifiers);
			counter += ft_display(arguments, &specifiers);
		}
		else
			counter += ft_print_char(*format);
		format++;
	}
	va_end(arguments);
	return (counter);
}
