/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:00:28 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:03:18 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst -> content);
	free(lst);
}

void	ft_lstdelone_key(t_lstk *lst, void (*del)(void*))
{
	if (lst)
	{
		if (lst->key)
			del(lst->key);
		if (lst->content)
			del(lst->content);
		free(lst);
	}
}
