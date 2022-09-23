/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_or_and.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:27:49 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 12:06:26 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_or_and2(char *s, int *i, int *a)
{
	if (*a == 1 && s[*i + 1] && ((s[*i] == '|'
				&& s[*i + 1] == '|') || (s[*i] == '&' && s[*i + 1] == '&')))
	{
		*a = -1;
		if (s[*i] == '&')
			(*a) = 0;
		if (s[*i + 1] && ((s[*i + 1] == '|' && *a == -1)
				|| (s[*i + 1] == '&' && *a == 0)))
			(*i)++;
		if (s[*i + 1] && ((s[*i] == '|' || s[*i] == '&')
				&& (s[*i + 1] == '|' || s[*i + 1] == ')' || s[*i + 1] == '(' )))
			return (0);
	}
	else if ((s[*i + 1] && s[*i] == '&' && s[*i + 1] != '&')
		|| (s[*i] == '&' && !s[*i + 1]))
		return (0);
	else if (s[*i] != ' ' && s[*i] != '\n')
		*a = 1;
	return (1);
}

int	check_or_and(char *str)
{
	int	i;
	int	a;

	i = -1;
	a = 1;
	if (!str)
		return (1);
	while (str[++i] && !g_all.orand)
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_qoute_inside(str + i);
		else if (!check_or_and2(str, &i, &a))
		{
			p_error(str[i]);
			g_all.orand = 1;
			return (0);
		}
	}
	return (a);
}

int	check_line_or_and(char *str)
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
		if (!*str || *str == '&' || *str == '|')
		{
			p_error(c);
			g_all.orand = 1;
			return (0);
		}
	}
	return (1);
}

static char	*ft_norm(char **line, char **str, int *a)
{
	if (!check_line_or_and(*str))
		return (NULL);
	*line = ft_strjoin2(*line, *str, 1);
	*a = check_or_and(*line);
	if (*a == 0 || *a == -1)
		free(g_all.herd);
	if (*a == 0)
		g_all.herd = ft_strdup("cmdand> ");
	else if (*a == -1)
		g_all.herd = ft_strdup("cmdor> ");
	return (*line);
}

char	*ft_or_and(char *line)
{
	char	*str;
	int		a;

	if (!line || !line[0])
		return (NULL);
	ft_norm2(line, &a);
	while ((a == -1 || a == 0) && !g_all.orand)
	{
		str = readline(g_all.herd);
		if (!str)
		{
			if (!g_all.no_init)
			{
				ft_putstr_fd(" Minishell : syntax error", 2);
				ft_putstr_fd(": unexpected end of file\n", 2);
			}
			g_all.no_init = 1;
			free(line);
			free(str);
			return (NULL);
		}
		if (!ft_norm(&line, &str, &a))
			return (NULL);
	}
	return (line);
}
