/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:56:35 by marvin            #+#    #+#             */
/*   Updated: 2019/11/17 14:56:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int      ft_minimum(int a, int b)
{
    if (a > b)
        return (b);
    else
        return (a);
}

static char     *ft_null_str(void)
{
    char    *str;

    str = (char*)malloc(sizeof(char) * 7);
    str[0] = '(';
    str[1] = 'n';
    str[2] = 'u';
    str[3] = 'l';
    str[4] = 'l';
    str[5] = ')';
    str[6] = '\0';
    return (str);
}

int             ft_display_string(va_list arguments, t_format *specifiers)
{
    int     counter;
    int     length;
    int     i;
    char    *str;
    char    *trash;

    counter = 0;
    if (!(str = va_arg(arguments, char *)))
        str = ft_null_str();
    if (specifiers->precision == -1)
        length = ft_strlen(str);
    else
        length = ft_minimum(ft_strlen(str), specifiers->precision);
    if (specifiers->flag_minus == 0)
        counter += ft_print_space(' ', specifiers->width_field - length);
    i = 0;
    trash = str;
    while (*str && length > i)
    {
        counter += ft_print_char(*str++);
        i++;
    }
    if (specifiers->flag_minus == 1)
        counter += ft_print_space(' ', specifiers->width_field - length);
    free(trash);
    return(counter);
}