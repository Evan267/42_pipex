/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:28:06 by eberger           #+#    #+#             */
/*   Updated: 2022/11/17 11:58:56 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_print_char(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

static int	ft_print_hexa(char c, unsigned long long x)
{
	char	*ptr;
	int		ret;

	ret = 0;
	if (c == 'x' || c == 'p')
		ptr = ft_convert_base(x, "0123456789", "0123456789abcdef");
	else
		ptr = ft_convert_base(x, "0123456789", "0123456789ABCDEF");
	if (ptr == 0)
		return (-1);
	if (c == 'p')
	{
		if (write(1, "0x", 2) == -1)
		{
			free(ptr);
			return (-1);
		}
		ret = 2;
	}
	ret += ft_print_str(ptr);
	free(ptr);
	return (ret);
}

int	ft_print_pourc(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_test_var(const char *s, int *i, va_list *args, int *len)
{
	int	ret;

	ret = 0;
	if (s[*i] == 'c')
		ret = ft_print_char((char)va_arg(*args, int));
	else if (s[*i] == 's')
		ret = ft_print_str(va_arg(*args, char *));
	else if (s[*i] == 'd' || s[*i] == 'i')
		ret = ft_print_int((long)va_arg(*args, int));
	else if (s[*i] == 'x' || s[*i] == 'X')
		ret = ft_print_hexa(s[*i], va_arg(*args, unsigned int));
	else if (s[*i] == 'u')
		ret = ft_print_int((long)va_arg(*args, unsigned int));
	else if (s[*i] == 'p')
		ret = ft_print_hexa(s[*i], va_arg(*args, unsigned long));
	else if (s[*i] == '%')
		ret = ft_print_pourc(s[*i]);
	if (ret == -1)
		return (-1);
	*len = *len + ret;
	return (*len);
}
