/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:30:20 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:01:43 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == 0)
		return (0);
	if (tmp)
	{
		tmp -> content = content;
		tmp -> next = NULL;
	}
	return (tmp);
}

t_lstk	*ft_lstnew_key(void *key, void *content)
{
	t_lstk	*new;

	new = NULL;
	new = (t_lstk *)malloc(sizeof(t_lstk));
	if (!new)
		return (NULL);
	new->key = key;
	new->content = content;
	new->next = NULL;
	return (new);
}
