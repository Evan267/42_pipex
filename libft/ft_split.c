/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:52:59 by eberger           #+#    #+#             */
/*   Updated: 2022/11/30 11:47:42 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_clear(char **ret)
{
	int	i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (0);
}

unsigned int	ft_count_string(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (ft_strchr(str, c) > str)
			count++;
		if (ft_strchr(str, c) != 0)
			str = ft_strchr(str, c) + 1;
		else
		{
			count++;
			break ;
		}
	}
	return (count);
}

char	**ft_part(char **ret, unsigned int *k, const char *s, char c)
{
	char	*strchr;

	strchr = ft_strchr(s + k[1], c);
	if (strchr)
	{
		if (strchr - s > k[1])
		{
			ret[k[0]] = malloc(strchr - s - k[1] + 1);
			if (!ret[k[0]])
				return (ft_clear(ret));
			ft_strlcpy(ret[k[0]], (char *)(s + k[1]), strchr - s - k[1] + 1);
			(k[0])++;
		}
		k[1] = strchr - s + 1;
	}
	else if (k[2])
	{
		ret[k[0]] = malloc(k[2] + 1);
		if (!ret[k[0]])
			return (ft_clear(ret));
		ft_strlcpy(ret[k[0]], (char *)(s + k[1]), k[2] + 1);
		(k[0])++;
		k[1] = k[1] + k[2];
	}
	return (ret);
}

char	**ft_add_part(const char *s, char c, char **ret)
{
	unsigned int	k[3];

	k[0] = 0;
	k[1] = 0;
	while ((ft_strchr(s + k[1], c) != 0 || ft_strlen(s + k[1])) && *s)
	{
		k[2] = (unsigned int)ft_strlen(s + k[1]);
		if (!ft_part(ret, k, s, c))
			return (0);
	}
	ret[k[0]] = 0;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	len_ptr;
	char			**ret;

	if (!s)
		return (0);
	if (!c && *s)
	{
		ret = malloc (sizeof(char *) * 2);
		if (!ret)
			return (0);
		ret[0] = malloc (sizeof(char) * (ft_strlen(s) + 1));
		if (!ret[0])
			return (ft_clear(ret));
		ft_strlcpy(ret[0], s, ft_strlen(s) + 1);
		ret[1] = 0;
		return (ret);
	}
	len_ptr = ft_count_string((char *)s, c);
	ret = malloc (sizeof(char *) * (len_ptr + 1));
	if (!ret)
		return (0);
	return (ft_add_part(s, c, ret));
}
