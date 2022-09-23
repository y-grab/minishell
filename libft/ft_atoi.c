/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:09:25 by gjohana           #+#    #+#             */
/*   Updated: 2022/02/10 19:46:55 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	return (i);
}	

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	digit;

	sign = 1;
	digit = 0;
	i = ft_space(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = digit * 10 + (str[i] - '0');
		i++;
		if (i >= 19 && sign == 1)
			return (-1);
		if (i >= 20 && sign == -1)
			return (0);
	}
	return (sign * digit);
}

long long	ft_atoll(char *s)
{
	int					i;
	int					neg;
	unsigned long long	ret;

	i = 0;
	ret = 0;
	neg = 1;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '-')
		neg = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = 10 * ret + s[i] - '0';
		i++;
	}
	ret = ret * neg;
	return (ret);
}
