/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:01:02 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 15:56:48 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_display_char(va_list arguments, t_format *specifiers)
{
	int		counter;
	int		c;

	counter = 0;
	if (specifiers->type_field == '%')
		c = '%';
	else
		c = (char)va_arg(arguments, int);
	if (specifiers->flag_minus == 0)
		counter += ft_print_space(' ', specifiers->width_field - 1);
	counter += ft_print_char(c);
	if (specifiers->flag_minus == 1)
		counter += ft_print_space(' ', specifiers->width_field - 1);
	return (counter);
}
