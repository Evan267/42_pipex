/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:26:26 by eberger           #+#    #+#             */
/*   Updated: 2022/11/01 10:14:18 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int chr)
{
	int	value;

	value = 1;
	if (chr < 0 || chr > 127)
		value = 0;
	return (value);
}
