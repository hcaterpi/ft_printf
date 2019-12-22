/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaterpi <hcaterpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:27:15 by hcaterpi          #+#    #+#             */
/*   Updated: 2019/12/22 15:27:44 by hcaterpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int			ft_nonnegative(int number)
{
	if (number < 0)
		number = 0;
	return (number);
}

char		ft_get_char(int number, char c)
{
	char	result;

	result = '0';
	while (number)
	{
		result++;
		if (result == ':')
			result = c;
		number--;
	}
	return (result);
}
