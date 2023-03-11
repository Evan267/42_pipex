/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:42:38 by eberger           #+#    #+#             */
/*   Updated: 2022/11/17 12:02:13 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (write(1, s + i, 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_print_str(char *str)
{
	int	ret;

	ret = 0;
	if (str)
	{
		ret = ft_putstr(str);
		if (ret == -1)
			return (-1);
		return (ret);
	}
	else
	{
		ret = ft_putstr("(null)");
		if (ret == -1)
			return (-1);
		return (ret);
	}
}
