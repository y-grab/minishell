/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:28:57 by gjohana           #+#    #+#             */
/*   Updated: 2021/10/19 13:30:08 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbr(int n, int fd)
{
	if (n == 0)
		write (fd, "0", 1);
	if (n == -2147483648)
	{
		write (fd, "-", 1);
		write (fd, "2", 1);
		n = 147483648;
		ft_putnbr_fd(n, fd);
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	arr[11];
	int		tmp;
	int		i;

	if (!fd)
		return ;
	if (n <= 0 || n == -2147483648)
	{
		ft_nbr(n, fd);
		return ;
	}
	tmp = n;
	i = 0;
	while (tmp)
	{
		arr[i++] = tmp % 10 + '0';
		tmp /= 10;
	}
	while (n)
	{
		write (fd, &arr[--i], 1);
		n /= 10;
	}
}
