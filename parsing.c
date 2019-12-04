/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:48:54 by marvin            #+#    #+#             */
/*   Updated: 2019/11/09 14:48:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_parse_flags(const char **format, t_format *specifier)
{
    while (*format)
	{
		if (**format == '-')
			specifier->flag_minus = 1;
		else if (**format == '+')
			specifier->flag_plus = 1;
		else if (**format == ' ')
			specifier->flag_space = 1;
		else if (**format == '#')
			specifier->flag_hash = 1;
		else if (**format == '0')
			specifier->flag_zero = 1;
		else
			break;
		(*format)++;
	}
}

static void		ft_parse_width_field(const char **format, t_format *specifier)
{
	while (**format >= '0' && **format <= '9')
	{
		specifier->width_field *= 10;
		specifier->width_field += **format - 48;
		(*format)++;
	}
}

static void		ft_parse_precision(const char **format, t_format *specifier)
{
    if (**format == '.')
	{
		specifier->precision = 0;
		(*format)++;
		while (**format >= '0' && **format <= '9')
		{
			specifier->precision *= 10;
			specifier->precision += **format - 48;
			(*format)++;
		}
	}
}

static void		ft_parse_length(const char **format, t_format *specifier)
{
	if (**format == 'h' && *(*format + 1) == 'h')
		specifier->length = hh;
	else if (**format == 'h')
		specifier->length = h;
	else if (**format == 'l' && *(*format + 1) == 'l')
		specifier->length = ll;
	else if (**format == 'l')
		specifier->length = l;
	else if (**format == 'L')
		specifier->length = L;
	else
		(*format)--;
	(*format)++;
	if (specifier->length == hh || specifier->length == ll)
		(*format)++;
}

void			ft_parse(const char **format, t_format *specifiers)
{
	if (**format == '%')
		specifiers->type_field = '%';
	else
	{
		ft_parse_flags(format, specifiers);
		ft_parse_width_field(format, specifiers);
		ft_parse_precision(format, specifiers);
		ft_parse_length(format, specifiers);
		specifiers->type_field = **format;
	}
}
