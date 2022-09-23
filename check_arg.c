/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:41:18 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 14:10:09 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_brackets(char *str)
{
	while (*str)
	{
		if (*str == 34 || *str == 39)
			str = skip_qoute(str);
		if (*str == 40 || *str == 41)
			*str = ' ';
		str++;
	}
}

char	*skip_qoute(char *str)
{
	if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
		if (*str && *str == '"')
			return (str++);
		return (str);
	}
	else
	{
		str++;
		while (*str && *str != '\'')
			str++;
		if (*str && *str == '\'')
			return (str++);
		return (str);
	}
}

int	check_error_brackets(int a)
{
	if (a > 0)
		p_error('(');
	else if (a < 0)
		p_error(')');
	g_all.orand = !!a;
	return (a);
}

char	*valid_brackets2(char *s, int *a, int *i, int *y)
{
	(*a)++;
	*y = (*i)++;
	while (*(++s) && (*s == ' ' || *s == '|' || *s == '&') && (i++))
	{
		if (*s == '|' || *s == '&')
		{
			p_error(*s);
			g_all.orand = 1;
			return (0);
		}
		(*y)++;
	}
	return (s);
}

int	valid_brackets(char *s)
{
	int		i;
	int		a;
	int		y;

	a = 0;
	i = 0;
	y = 0;
	while (*s && a >= 0)
	{
		if (*s == '\'' || *s == '\"')
			s = skip_qoute(s);
		else if (*s == '(')
			s = valid_brackets2(s, &a, &i, &y);
		else if (*s == ')' && y + 1 != i && ++i && s++)
			a--;
		else if (++i && s++)
			;
	}
	return (check_error_brackets(a));
}
