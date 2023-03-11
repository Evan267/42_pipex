/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:52:37 by eberger           #+#    #+#             */
/*   Updated: 2022/11/17 12:02:40 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_count_char_long(long nbr)
{
	int	i;

	i = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	nbr /= 10;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	ft_print_int(long nb)
{
	int		len;
	char	c;

	len = ft_count_char_long(nb);
	if (nb < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		nb = -nb;
	}
	if (nb >= 10)
	{
		if (ft_print_int(nb / 10) == -1)
			return (-1);
		if (ft_print_int(nb % 10) == -1)
			return (-1);
	}
	if (nb < 10)
	{
		c = nb + '0';
		if (write(1, &c, 1) == -1)
			return (-1);
	}
	return (len);
}
