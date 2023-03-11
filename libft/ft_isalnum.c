/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:46:54 by eberger           #+#    #+#             */
/*   Updated: 2022/11/02 10:47:12 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int chr)
{
	int	value;

	value = 1;
	if (!ft_isalpha(chr) && !ft_isdigit(chr))
		value = 0;
	return (value);
}
