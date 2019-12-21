/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 19:13:41 by marvin            #+#    #+#             */
/*   Updated: 2019/12/21 19:13:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_reverse(char *str, int i)
{
	int		length;
	char	c;

	length = i;
	while (i > length / 2)
	{
		c = str[length - i];
		str[length - i] = str[i];
		str[i] = c;
		i--;
	}
}

static void		ft_rounding(char* str, int i)
{
	int		overflow;
	int		j;
 
	j = i + 1;
	overflow = 1;
	while (j--)
	{
		str[j] += overflow;
		if(str[j] > '9' && (overflow = 1))
			str[j] = '0';
		else if (str[j] != '.' && (overflow = 0))
			break;
	}
	if (overflow)
	{
		j = i + 1;
		while (j--)
			str[j] = str[j - 1];
		str[i] = '1';
	}
}

static int       ft_integer(long double number, char *str)
{
    long    integer;
    int     i;

    i = 0;
	if ((integer = (long)number))
	{
		while (integer)
		{
			str[i++] = '0' + integer % 10;
			integer /= 10;
		}
		ft_reverse(str, i - 1);
	}
	else
		str[i++] = '0';
    return (i);
}

static void     ft_decimal(long double number, char *str, int precision, int i)
{
	double	decimal;

	decimal = number - (long)number;
	if (precision > 0)
	{
		str[i++] = '.';
		while (precision--)
		{
			decimal *= 10;
			str[i++] = '0' + (long)decimal;
			decimal -= (long)decimal;
		}
		if ((long)(decimal + 0.5))
			ft_rounding(str, i - 1);
	}
}

char		    *ft_ftoa(long double number, t_format *specifiers)
{
	long    integer;
    int		length;
    char	*str;

	length = 0;
	if (specifiers->precision > 0)
		length = specifiers->precision + 1;
    integer = (long)number;
	while (integer && ++length)
        integer /= 10;
	str = (char*)malloc(sizeof(char) * (length + 1));
    str[length] = '\0';
    ft_decimal(number, str, specifiers->precision, ft_integer(number, str));
	return (str);
}