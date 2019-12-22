/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hexadec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:09:59 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 19:11:53 by hcaterpi         ###   ########.fr       */
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

static char			*ft_zero_str(int precision)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 2);
	str[0] = '0';
	str[1] = '\0';
	if (precision == 0)
		str[0] = '\0';
	return (str);
}

static char			*ft_itoa_base(unsigned long number, t_format *specifiers)
{
	unsigned long	buffer;
	int				length;
	char			*str;

	if (number == 0)
		return (ft_zero_str(specifiers->precision));
	length = 0;
	buffer = number;
	while (buffer && ++length)
		buffer /= 16;
	str = (char*)malloc(sizeof(char) * (length + 1));
	str[length] = '\0';
	buffer = number;
	while (buffer)
	{
		str[length - 1] = ft_get_char(buffer % 16, specifiers->type_field - 23);
		buffer /= 16;
		length--;
	}
	return (str);
}

int					ft_display_hexadec(va_list arguments, t_format *specifiers)
{
	int				counter;
	int				length;
	unsigned long	number;
	char			*str;

	counter = 0;
	if (!(number = ft_get_number(arguments, specifiers)))
		specifiers->flag_hash = 0;
	str = ft_itoa_base(number, specifiers);
	length = ft_strlen(str);
	if (specifiers->flag_minus == 0 && specifiers->flag_zero == 0)
		counter += ft_print_space(' ', specifiers->width_field
		- length - 2 * specifiers->flag_hash);
	if (specifiers->flag_hash == 1 && (counter += ft_print_char('0')))
		counter += ft_print_char(specifiers->type_field);
	if (specifiers->flag_zero == 1)
		counter += ft_print_space('0', specifiers->width_field
		- length - 2 * specifiers->flag_hash);
	counter += ft_print_space('0', specifiers->precision - length);
	counter += ft_print_string(str);
	if (specifiers->flag_minus == 1)
		counter += ft_print_space(' ', specifiers->width_field
		- length - 2 * specifiers->flag_hash);
	free(str);
	return (counter);
}
