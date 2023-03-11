/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:29:24 by eberger           #+#    #+#             */
/*   Updated: 2022/11/05 15:33:18 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*src;
	size_t	i;

	src = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)src[i] == (unsigned char)c)
			return (src + i);
		i++;
	}
	return (0);
}
