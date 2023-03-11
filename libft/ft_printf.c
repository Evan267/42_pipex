/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:41:38 by eberger           #+#    #+#             */
/*   Updated: 2022/11/17 11:21:00 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		len;
	int		i;
	va_list	args;

	va_start(args, s);
	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != '%')
		{
			if (write(1, s + i, 1) == -1)
				return (-1);
			len++;
		}
		else
		{
			i++;
			if (ft_test_var(s, &i, &args, &len) == -1)
				return (-1);
		}
		i++;
	}
	va_end(args);
	return (len);
}
