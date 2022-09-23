/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:43:28 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 11:13:04 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		l1;
	int		l2;
	char	*res;

	l1 = ft_strlen2(s1);
	l2 = ft_strlen2(s2);
	if (!(l1 + l2))
	{
		(ft_free_gnl(&s1) || ft_free_gnl(&s2));
		return (NULL);
	}
	res = (char *)malloc(l1 + l2 + 1);
	if (!res)
		return (ft_free_gnl(&s1));
	i = -1;
	while (++i < l1)
		res[i] = s1[i];
	i = -1;
	while (++i < l2)
		res[i + l1] = s2[i];
	res[l1 + l2] = 0;
	(ft_free_gnl(&s1) || ft_free_gnl(&s2));
	return (res);
}

char	*ft_substr_gnl(char *s, int end)
{
	char	*sub;
	int		i;

	if (!s[0])
		return (ft_free_gnl(&s));
	i = -1;
	sub = (char *)malloc(end + 2);
	if (!sub)
		return (ft_free_gnl(&s));
	while (++i <= end)
		sub[i] = s[i];
	sub[end + 1] = 0;
	return (sub);
}

void	ft_new_buff_gnl(char **buff, int start)
{
	char	*new;
	int		end;

	end = 0;
	while ((*buff)[end + start])
		end++;
	if (!end)
	{
		ft_free_gnl(buff);
		return ;
	}
	new = ft_substr_gnl((*buff) + start, end - 1);
	ft_free_gnl(buff);
	*buff = new;
}
