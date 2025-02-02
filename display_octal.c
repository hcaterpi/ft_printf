/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_octal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 14:27:04 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 18:54:05 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t		ft_get_number(va_list arguments, t_format *specifiers)
{
	intmax_t	n;

	if (specifiers->length == 1)
		n = (unsigned char)(va_arg(arguments, unsigned int));
	else if (specifiers->length == 2)
		n = (unsigned short)(va_arg(arguments, unsigned int));
	else if (specifiers->length == 3)
		n = (unsigned long long)(va_arg(arguments, unsigned long long int));
	else if (specifiers->length == 4)
		n = (unsigned long)(va_arg(arguments, unsigned long int));
	else
		n = (unsigned int)(va_arg(arguments, unsigned int));
	return (n);
}

static char			*ft_zero_str(t_format *specifiers)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 2);
	str[0] = '0';
	str[1] = '\0';
	if (!specifiers->precision && !specifiers->flag_hash)
		str[0] = '\0';
	return (str);
}

static char			*ft_itoa_base(unsigned long n, t_format *specifiers)
{
	unsigned long	buffer;
	int				length;
	char			*str;

	if (n == 0)
		return (ft_zero_str(specifiers));
	length = 0;
	if (specifiers->flag_hash == 1)
		length++;
	buffer = n;
	while (buffer && ++length)
		buffer /= 8;
	str = (char*)malloc(sizeof(char) * (length + 1));
	if (specifiers->flag_hash == 1)
		str[0] = '0';
	str[length] = '\0';
	buffer = n;
	while (buffer)
	{
		str[length - 1] = ft_get_char(buffer % 8, 'a');
		buffer /= 8;
		length--;
	}
	return (str);
}

int					ft_display_octal(va_list arguments, t_format *specifiers)
{
	int			counter;
	int			length;
	intmax_t	number;
	char		*str;

	counter = 0;
	number = ft_get_number(arguments, specifiers);
	str = ft_itoa_base(number, specifiers);
	length = ft_strlen(str);
	if (specifiers->flag_minus == 0 && specifiers->flag_zero == 0)
		counter += ft_print_space(' ', specifiers->width_field - length
		- ft_nonnegative(specifiers->precision - length));
	if (specifiers->flag_zero == 1)
		counter += ft_print_space('0', specifiers->width_field
		- length - 2 * specifiers->flag_hash);
	else if (specifiers->precision)
		counter += ft_print_space('0', specifiers->precision
		- length - 2 * specifiers->flag_hash);
	counter += ft_print_string(str);
	if (specifiers->flag_minus == 1)
		counter += ft_print_space(' ', specifiers->width_field - length
		- ft_nonnegative(specifiers->precision - length));
	free(str);
	return (counter);
}
