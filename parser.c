/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:09:38 by ujicama           #+#    #+#             */
/*   Updated: 2022/07/02 11:24:55 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(char *str, int *i, int *a)
{
	if ((str[*i] == ' ' || str[*i] == '\0') && *a % 2 != 0)
		return (syn_backslash_exit());
	if (str[*i] != ' ' && str[*i] != '\0')
	{
		*a -= 1;
		if (*a % 2 != 0)
			return (syn_backslash_exit());
	}
	return (0);
}

static int	check2(char *str, int *i, int *a, int *sq)
{
	if ((str[*i] == '\\' && str[*i - 1] != '\\' && (sq > 0 \
		&& (str[*i + 1] == ' ' || str[*i + 1] == '\0'))) || (*a % 2) != 0)
		return (syn_backslash_exit());
	return (0);
}

static void	init(int *i, int *sq, int *dq, int *a)
{
	*a = 0;
	*i = 0;
	*sq = 1;
	*dq = 1;
}

int	syn_backslash(char *str)
{
	int	i;
	int	sq;
	int	dq;
	int	a;

	init(&i, &sq, &dq, &a);
	while (str[i] != '\0')
	{
		syn_error_qoutes(str, i, &sq, &dq);
		if (str[i] == '\\' && str[i + 1] == '\\' && sq > 0)
		{
			while (str[i] && str[i] == '\\' && sq > 0)
			{
				i++;
				a++;
				syn_error_qoutes(str, i, &sq, &dq);
			}
			if (check(str, &i, &a))
				return (1);
		}
		if (check2(str, &i, &a, &sq))
			return (1);
		i++;
	}
	return (0);
}

char	*parser(char *str)
{
	int	i;
	int	sq;
	int	dq;

	sq = 1;
	dq = 1;
	i = -1;
	if (syn_backslash(str))
	{
		printf("\\ not supported\n");
	}
	while (str[++i])
	{
		syn_error_qoutes(str, i, &sq, &dq);
		if (str[i] == '\\' && sq > 0)
		{
			str = process_backslash(str, &i);
		}
	}
	return (str);
}
