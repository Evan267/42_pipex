/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:59:20 by eberger           #+#    #+#             */
/*   Updated: 2022/11/30 11:33:47 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lmap(t_list *l, t_list *n, void *(*f)(void *), void (*del)(void *))
{
	void	*tmp;
	t_list	*ptr;

	while (l)
	{
		tmp = (*f)(l->content);
		ptr = ft_lstnew(tmp);
		if (!ptr)
		{
			del(tmp);
			ft_lstclear(&n, del);
			return (0);
		}
		ft_lstadd_back(&n, ptr);
		l = l->next;
	}
	return (n);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*tmp;

	if (!lst)
		return (0);
	tmp = (*f)(lst->content);
	new = ft_lstnew(tmp);
	if (!new)
	{
		del(tmp);
		return (0);
	}
	lst = lst->next;
	return (ft_lmap(lst, new, f, del));
}
