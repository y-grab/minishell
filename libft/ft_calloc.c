/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:53:34 by gjohana           #+#    #+#             */
/*   Updated: 2021/10/18 19:03:04 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	length;
	unsigned int	i;
	char			*dest;

	length = count * size;
	dest = (char *)malloc(length);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (length != 0)
	{
		dest[i] = 0;
		i++;
		length--;
	}
	return (dest);
}
