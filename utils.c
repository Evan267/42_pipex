/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:16:36 by eberger           #+#    #+#             */
/*   Updated: 2023/03/27 16:50:16 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_3_str(char *str1, char *str2, char *str3)
{
	char	*c;

	c = str1;
	str1 = ft_strjoin(str1, str2);
	free(c);
	c = str1;
	str1 = ft_strjoin(str1, str3);
	free(c);
	return (str1);
}

void	trim_by_char(char **ret, char c)
{
	char	*tmp;
	char	trim[2];

	trim[0] = c;
	trim[1] = 0;
	tmp = *ret;
	*ret = ft_strtrim(*ret, trim);
	free(tmp);
}
