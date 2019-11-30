/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:40:45 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/11/30 15:16:16 by marvin           ###   ########.fr       */
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

void			ft_show_test_info(t_format *specifiers)		// DELETE !!!
{
	printf("Flag minus = %d\n", specifiers->flag_minus);
	printf("Flag plus = %d\n", specifiers->flag_plus);
	printf("Flag space = %d\n", specifiers->flag_space);
	printf("Flag hash = %d\n", specifiers->flag_hash);
	printf("Flag zero = %d\n", specifiers->flag_zero);
	printf("Width field = %d\n", specifiers->width_field);
	printf("Precision = %d\n", specifiers->precision);
	printf("Length = %d\n", specifiers->length);
	printf("Type field = %c\n", specifiers->type_field);
}

int				ft_printf(const char *format, ...)
{
	int		counter;
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
			//ft_show_test_info(&specifiers);
			counter += ft_display(arguments, &specifiers);
		}
		else
			counter += ft_print_char(*format);
		format++;
	}
	va_end(arguments);
	return (counter);
}
