/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:18:29 by eberger           #+#    #+#             */
/*   Updated: 2022/11/05 16:39:46 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char(int n)
{
	int		i;
	long	nbr;

	i = 1;
	nbr = n;
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

void	ft_convtoi(int n, char *ptr, int i)
{
	long	nbr;

	ptr[i--] = 0;
	nbr = n;
	if (n < 0)
	{
		ptr[0] = '-';
		nbr = -nbr;
	}
	if (n == 0)
		ptr[0] = '0';
	while (i >= 0 && (nbr / 10 > 0 || nbr % 10 > 0))
	{
		ptr[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;

	size = ft_count_char(n) + 1;
	ptr = malloc(size);
	if (ptr == 0)
		return (0);
	ft_convtoi(n, ptr, size - 1);
	return (ptr);
}
