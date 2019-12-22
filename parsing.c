/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:26:50 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 16:21:03 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_parse_flags(const char **format, t_format *specifiers)
{
	while (*format)
	{
		if (**format == '-')
			specifiers->flag_minus = 1;
		else if (**format == '+')
			specifiers->flag_plus = 1;
		else if (**format == ' ')
			specifiers->flag_space = 1;
		else if (**format == '#')
			specifiers->flag_hash = 1;
		else if (**format == '0')
			specifiers->flag_zero = 1;
		else
			break ;
		(*format)++;
	}
	if (specifiers->flag_minus)
		specifiers->flag_zero = 0;
}

static void		ft_parse_width_field(const char **format, t_format *specifiers)
{
	while (**format >= '0' && **format <= '9')
	{
		specifiers->width_field *= 10;
		specifiers->width_field += **format - 48;
		(*format)++;
	}
}

static void		ft_parse_precision(const char **format, t_format *specifiers)
{
	if (**format == '.')
	{
		specifiers->precision = 0;
		(*format)++;
		while (**format >= '0' && **format <= '9')
		{
			specifiers->precision *= 10;
			specifiers->precision += **format - 48;
			(*format)++;
		}
	}
}

static void		ft_parse_length(const char **format, t_format *specifiers)
{
	if (**format == 'h' && *(*format + 1) == 'h')
		specifiers->length = hh;
	else if (**format == 'h')
		specifiers->length = h;
	else if (**format == 'l' && *(*format + 1) == 'l')
		specifiers->length = ll;
	else if (**format == 'l')
		specifiers->length = l;
	else if (**format == 'L')
		specifiers->length = L;
	else
		(*format)--;
	(*format)++;
	if (specifiers->length == hh || specifiers->length == ll)
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
