/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:13:46 by marvin            #+#    #+#             */
/*   Updated: 2019/11/17 15:13:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t		ft_get_number(va_list arguments, t_format *specifiers)
{
	intmax_t	number;

	if (specifiers->length == 1)
		number = (unsigned char)(va_arg(arguments, unsigned int));
	else if (specifiers->length == 2)
		number = (unsigned short)(va_arg(arguments, unsigned int));
	else if (specifiers->length == 3)
		number = (unsigned long long)(va_arg(arguments, unsigned long long int));
	else if (specifiers->length == 4)
		number = (unsigned long)(va_arg(arguments, unsigned long int));
	else
		number = (unsigned int)(va_arg(arguments, unsigned int));
	return (number);
}

static char         *ft_zero_str(void)
{
    char    *str;

    str = (char*)malloc(sizeof(char) * 2);
    str[0] = '0';
    str[1] = '\0';
    return (str);
}

static char         *ft_itoa_base(unsigned long number, int base, char c, t_format *specifiers)
{
    unsigned long   buffer;
    int             length;
    char            *str;

    if (number == 0)
        return (ft_zero_str());
    length = 0;
    if (specifiers->flag_hash == 1)
		length += 2;
    buffer = number;
    while (buffer && length++)
        buffer /= base;
    str = (char*)malloc(sizeof(char) * (length + 1));
    if (specifiers->flag_hash == 1 && (str[0] = '0'))
        str[1] = c + 23;
    str[length] = '\0';
    buffer = number;
    while (buffer)
    {
        str[length - 1] = ft_get_char(buffer % base, c);
        buffer /= base;
        length--;
    }
    return (str);
}

int                 ft_display_hexadecimal(va_list arguments, t_format *specifiers)
{
    int             counter;
    int             length;
    unsigned long	number;
    char            *str;
    char            *trash;

    counter = 0;
    number = ft_get_number(arguments, specifiers);
	str = ft_itoa_base(number, 16, specifiers->type_field - 23, specifiers);
	length = ft_strlen(str);
    if (specifiers->flag_minus == 0)
        counter += ft_print_space(' ', specifiers->width_field - length);
    trash = str;
    while (*str)
        counter += ft_print_char(*str++);
    if (specifiers->flag_minus == 1)
        counter += ft_print_space(' ', specifiers->width_field - length);
    free(trash);
    return (counter);
}
