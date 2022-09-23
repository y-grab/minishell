/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:02:48 by gjohana           #+#    #+#             */
/*   Updated: 2021/10/19 13:17:33 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_nb(long nb)
{
	int	size;

	size = 0;
	if (nb < 0)
	{
		size += 1;
		nb = -nb;
	}
	else if (nb == 0)
		size += 1;
	while (nb)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

static char	*ft_fill_nb(char *dest, long nb, int len)
{
	dest[len] = '\0';
	if (nb < 0)
	{
		dest[0] = '-';
		nb = -nb;
	}
	else if (nb == 0)
		dest[0] = '0';
	while (nb)
	{
		dest[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;
	long	nb;

	nb = (long)n;
	len = ft_count_nb(nb);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	ft_fill_nb(dest, nb, len);
	return (dest);
}
