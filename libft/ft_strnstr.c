/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:06:40 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/26 15:30:06 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack && haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && j + i < len
			&& haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
