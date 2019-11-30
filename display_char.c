/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:57:08 by marvin            #+#    #+#             */
/*   Updated: 2019/11/17 14:57:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int    ft_display_char(va_list arguments, t_format *specifiers)
{
    int     counter;
    int     c;

    counter = 0;
    c = (char)va_arg(arguments, int);
    if (specifiers->flag_minus == 0)
        counter += ft_print_space(' ', specifiers->width_field - 1);
    counter += ft_print_char(c);
    if (specifiers->flag_minus == 1)
        counter += ft_print_space(' ', specifiers->width_field - 1);
    return(counter);
}
