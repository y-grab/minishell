/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdoublejoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:59:35 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:01:20 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_data2(char **s, int len)
{
	while (len--)
		s[len] = NULL;
}

char	**ft_strdoublejoin(char ***s1, char **s2, int l1, int l2)
{
	int		i;
	int		j;
	char	**new;

	new = (char **)malloc(sizeof(char *) * (l1 + l2 + 1));
	init_data2(new, l1 + l2 + 1);
	i = -1;
	j = 0;
	while (++i < l1 && (*s1)[i])
		new[j++] = (*s1)[i];
	i = -1;
	while (++i < l2)
	{
		new[j++] = s2[i];
		s2[i] = NULL;
	}
	free(*s1);
	*s1 = NULL;
	return (new);
}

static void	*ft_free(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		l1;
	int		l2;
	char	*res;

	l1 = ft_strlen2(s1);
	l2 = ft_strlen2(s2);
	if (!(l1 + l2))
	{
		(ft_free(&s1) || ft_free(&s2));
		return (NULL);
	}
	res = (char *)malloc(l1 + l2 + 1);
	if (!res)
		return (ft_free(&s1));
	i = -1;
	while (++i < l1)
		res[i] = s1[i];
	i = -1;
	while (++i < l2)
		res[i + l1] = s2[i];
	res[l1 + l2] = 0;
	(ft_free(&s1) || ft_free(&s2));
	return (res);
}
