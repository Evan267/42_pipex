/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:09:26 by eberger           #+#    #+#             */
/*   Updated: 2022/11/05 14:18:44 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t	i;
	char	*d;

	i = 0;
	if (!dst && !src)
		return (0);
	d = (char *)dst;
	while (i < n)
	{
		*(char *)d = *(char *)src;
		d++;
		src++;
		i++;
	}
	return (dst);
}
