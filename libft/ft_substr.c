/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:38:05 by gjohana           #+#    #+#             */
/*   Updated: 2021/10/22 14:34:38 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_start(char const *s, unsigned int start)
{
	size_t	length;

	length = ft_strlen(s);
	if (start > length)
		start = length;
	return (start);
}

static int	check_len(char const *s, unsigned int start, size_t len)
{
	size_t	length;

	length = ft_strlen(s);
	if (len > length - start)
		len = length - start;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	start = check_start(s, start);
	len = check_len(s, start, len);
	dest = (char *)malloc(sizeof(*s) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			dest[j] = s[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
