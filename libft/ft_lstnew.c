/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:33:38 by eberger           #+#    #+#             */
/*   Updated: 2022/11/06 11:43:50 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = 0;
	tmp = malloc(sizeof(t_list));
	if (tmp)
	{
		tmp->content = content;
		tmp->next = 0;
	}
	return (tmp);
}
