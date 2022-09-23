/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:04:47 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 14:10:22 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space_and(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (str[i] == '&')
	{
		a = i;
		i++;
		if (str[i] == '|')
		{
			p_error(str[i]);
			g_all.orand = 1;
			return (0);
		}
		while (str[i] && (str[i] == '\n' || str[i] == ' '))
			i++;
		if (str[i] && str[i] == '|' && a + 1 != i)
		{
			p_error(str[i]);
			g_all.orand = 1;
			return (0);
		}
	}
	return (1);
}

int	check_space_pipe(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (str && str[i] == '|')
	{
		a = i;
		i++;
		while (str[i] && (str[i] == '\n' || str[i] == ' '))
			i++;
		if (str[i] && str[i] == '|' && a + 1 != i)
		{
			p_error(str[i]);
			g_all.orand = 1;
			return (0);
		}
	}
	return (1);
}

int	check_line_pipe(char *str)
{
	char	c;

	while (*str && (*str == ' ' || *str == '\n'))
		str++;
	if (*str && (*str == '|' || *str == '&'))
	{
		c = *str;
		str++;
		while (*str && (*str == ' ' || *str == '\n'))
			str++;
		if (!*str)
		{
			p_error(c);
			g_all.orand = 1;
			return (0);
		}
	}
	return (1);
}
