/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:15:40 by eberger           #+#    #+#             */
/*   Updated: 2023/03/09 13:19:31 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		ft_test_var(const char *s, int *i, va_list *args, int *len);
char	*ft_convert_base(unsigned long nbr, char *base_from, char *base_to);
int		ft_print_str(char *str);
int		ft_print_int(long nb);

#endif
