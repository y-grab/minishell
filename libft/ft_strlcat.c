/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:14:37 by gjohana           #+#    #+#             */
/*   Updated: 2021/10/18 18:07:27 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	linelength;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
		j++;
	if (i >= dstsize)
		return (j + dstsize);
	else
	{
		linelength = i + j;
		j = 0;
		while (src[j] && (i + 1) < dstsize)
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (linelength);
}
