/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:54:34 by gjohana           #+#    #+#             */
/*   Updated: 2021/10/19 17:37:40 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_first_elem(t_list *lst, void *(*f)(void *),
		void (*del)(void *))
{
	t_list	*new;

	new = ft_lstnew(f(lst -> content));
	if (!new)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	new = ft_first_elem(lst, f, del);
	tmp = new;
	lst = lst -> next;
	while (lst)
	{
		new = ft_lstnew(f(lst -> content));
		if (!new)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		lst = lst -> next;
		ft_lstadd_back(&tmp, new);
	}
	return (tmp);
}
