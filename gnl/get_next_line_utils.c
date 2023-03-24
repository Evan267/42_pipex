/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:52:19 by eberger           #+#    #+#             */
/*   Updated: 2022/12/20 09:35:43 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clear(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = 0;
	while (dest[dlen])
		dlen++;
	slen = 0;
	while (src[slen])
		slen++;
	if (size == 0)
		return (slen);
	i = 0;
	if (size < dlen)
		return (slen + size);
	while (src[i] != 0 && dlen + i < size - 1)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

int	ft_linelen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == 0)
		return (-1);
	i++;
	return (i);
}

void	*ft_realloc(void *ptr, size_t size, size_t msize)
{
	void	*new;
	char	*str;
	size_t	i;

	i = 0;
	str = ptr;
	if (size <= msize)
		return (ptr);
	new = ft_calloc(1, size);
	if (!new)
		return (ft_clear(&str));
	if (str)
	{
		while (str[i])
			i++;
		ft_strlcat(new, str, i + 1);
		free(str);
	}
	return (new);
}
