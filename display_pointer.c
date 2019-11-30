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

static char     *ft_itoa_base(unsigned long number, int base, char c)
{
    unsigned long   buffer;
    int             length;
    char            *str;

    length = 0;
    buffer = number;
    while (buffer)
    {
        buffer /= base;
        length++;
    }
    str = (char*)malloc(sizeof(char) * (length + 3));
    str[0] = '0';
    str[1] = 'x';
    str[length + 2] = '\0';
    buffer = number;
    while (buffer)
    {
        str[length + 1] = ft_get_char(buffer % base, c);
        buffer /= base;
        length--;
    }
    return (str);
}

static char     *ft_nil_str(void)
{
    char    *str;

    str = (char*)malloc(sizeof(char) * 6);
    str[0] = '(';
    str[1] = 'n';
    str[2] = 'i';
    str[3] = 'l';
    str[4] = ')';
    str[5] = '\0';
    return (str);
}

int             ft_display_pointer(va_list arguments, t_format *specifiers)
{
    int             counter;
    int             length;
    unsigned long	number;
    char            *str;
    char            *trash;

    counter = 0;
    if ((number = (unsigned long)(va_arg(arguments, unsigned long int))))
        str = ft_itoa_base(number, 16, 'a');
    else
        str = ft_nil_str();
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