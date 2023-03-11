/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:31:42 by eberger           #+#    #+#             */
/*   Updated: 2022/11/06 14:45:58 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = malloc(len);
	if (ptr == 0)
		return (0);
	ft_strlcpy(ptr, (char *)s1, len);
	ft_strlcat(ptr, (char *)s2, len);
	ptr[ft_strlen(ptr)] = 0;
	return (ptr);
}
