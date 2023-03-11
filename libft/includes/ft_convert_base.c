/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:36:16 by eberger           #+#    #+#             */
/*   Updated: 2022/11/17 11:49:14 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_error_base(char *b, int blen)
{
	int	i;
	int	j;

	i = 0;
	if (blen <= 1)
		return (1);
	while (b[i] != 0)
	{
		if (b[i] == 43 || b[i] == 45 || b[i] == 32 || (b[i] >= 9 && b[i] <= 13))
			return (1);
		j = i + 1;
		while (b[j] != 0)
		{
			if (b[j] == b[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_len_convert_nb(unsigned long nb, int base_len)
{
	int	i;

	i = 1;
	if (nb < 0)
		nb = -nb;
	while (nb / base_len > 0)
	{
		i++;
		nb /= base_len;
	}
	return (i);
}

static char	*ft_save(unsigned long nbl, char *base, int len_convert, int neg)
{
	int		base_len;
	char	*result;

	base_len = ft_strlen(base);
	result = malloc(sizeof(char) * (len_convert + 1));
	if (result == 0)
		return (0);
	result[len_convert] = '\0';
	len_convert--;
	while (len_convert >= 0 && nbl >= 0)
	{
		result[len_convert] = base[nbl % base_len];
		len_convert--;
		nbl /= base_len;
	}
	if (neg == 1)
		result[0] = '-';
	return (result);
}

static char	*ft_convert(unsigned long nb, char *base, int base_len)
{
	char	*result;
	int		len_convert;

	len_convert = ft_len_convert_nb(nb, base_len);
	if (nb < 0)
	{
		len_convert += 1;
		result = ft_save(-nb, base, len_convert, 1);
	}
	else
		result = ft_save(nb, base, len_convert, 0);
	return (result);
}

char	*ft_convert_base(unsigned long nbr, char *base_from, char *base_to)
{
	int		len_base_from;
	int		len_base_to;
	char	*ret;

	len_base_from = ft_strlen(base_from);
	len_base_to = ft_strlen(base_to);
	if (ft_error_base(base_from, len_base_from) == 1
		|| ft_error_base(base_to, len_base_to) == 1)
		return (0);
	ret = ft_convert(nbr, base_to, len_base_to);
	return (ret);
}
