/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:36:09 by gjohana           #+#    #+#             */
/*   Updated: 2021/10/18 19:17:53 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_symbols(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_end(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	i -= 1;
	while (i > 0)
	{
		if (ft_check_symbols(s1[i], set) == 0)
			return (i);
		i--;
	}
	return (0);
}

static int	ft_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (ft_check_symbols(s1[i], set) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	size;
	char	*dest;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	if (start == end)
	{
		dest = (char *)malloc(end - start + 1);
		if (dest == NULL)
			return (NULL);
		dest[0] = '\0';
	}
	else
	{
		size = end - start;
		dest = ft_substr(s1, start, size + 1);
	}
	return (dest);
}
