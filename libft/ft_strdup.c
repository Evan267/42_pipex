/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:04:36 by eberger           #+#    #+#             */
/*   Updated: 2022/11/04 14:36:51 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		src_len;
	char	*str;
	int		i;

	src_len = ft_strlen(src);
	str = malloc(src_len + 1);
	if (str == 0)
		return (0);
	i = 0;
	while (src[i])
	{
		str[i] = (char)src[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
