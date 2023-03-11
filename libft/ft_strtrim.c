/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:47:17 by eberger           #+#    #+#             */
/*   Updated: 2022/11/06 15:29:58 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ptr;

	start = 0;
	end = ft_strlen(s1);
	if (!ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[end - 1]))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	ptr = malloc(end - start + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1 + start, end - start + 1);
	return (ptr);
}
