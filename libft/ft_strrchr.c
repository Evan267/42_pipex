/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:07:27 by eberger           #+#    #+#             */
/*   Updated: 2022/11/05 15:11:38 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s) - 1;
	if ((unsigned char)c == 0)
		return ((char *)(s + len + 1));
	while (len >= 0)
	{
		if ((unsigned char)s[len] == (unsigned char)c)
			return ((char *)(s + len));
		len--;
	}
	return (0);
}
