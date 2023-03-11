/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:42:36 by eberger           #+#    #+#             */
/*   Updated: 2022/11/06 14:21:45 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	i = ft_strlen(s + start);
	if (i < len)
		len = i;
	ptr = malloc(len + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, (char *)(s + start), len + 1);
	return (ptr);
}
