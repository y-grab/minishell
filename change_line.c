/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:02:36 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 13:35:33 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_symbole(char *str)
{
	int	i;
	int	a;

	i = -1;
	a = 0;
	while (str[++i])
		if (str[i] == '>' || str[i] == '<')
			a++;
	return (a * 2);
}

void	add_space_line1(char *s, char *str, int *i, int *j)
{
	str[(*j)++] = ' ';
	str[(*j)++] = s[(*i)++];
	str[(*j)++] = s[(*i)++];
	str[(*j)++] = ' ';
}

void	add_space_line2(char *s, char *str, int *i, int *j)
{
	str[(*j)++] = ' ';
	str[(*j)++] = s[(*i)++];
	str[(*j)++] = ' ';
}

void	add_space_line3(char *s, char *str, int *i, int *j)
{
	int	type;

	type = (s[(*i)] == '\'') + 2 * (s[(*i)] == '\"');
	if (type)
		str[(*j)++] = s[(*i)++];
	while (type && s[(*i)] && ((type == 1 && s[(*i)] != '\'')
			|| (type == 2 && s[(*i)] != '\"')))
		str[(*j)++] = s[(*i)++];
	str[(*j)++] = s[(*i)++];
}

char	*change_line(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen2(s) + count_symbole(s) + 1);
	while (s[i])
	{
		if (s[i + 1] && ((s[i] == '>' && s[i + 1] == '>')
				|| (s[i] == '<' && s[i + 1] == '<')))
			add_space_line1(s, str, &i, &j);
		else if (s[i] == '>' || s[i] == '<')
			add_space_line2(s, str, &i, &j);
		else
			add_space_line3(s, str, &i, &j);
	}
	free(s);
	str[j] = '\0';
	return (str);
}
