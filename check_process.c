/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:15:29 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 21:28:51 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_qoute_inside(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		return (i);
	}
	else
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		return (i);
	}
}

int	check_pipe(char *str, int len)
{
	int	i;
	int	a;

	i = -1;
	a = 1;
	check_space(str);
	while (!g_all.orand && str && ++i < len)
	{
		if (str[i] == '&' && !check_space_and(str + i))
			return (0);
		if (str[i] == '\'' || str[i] == '"')
			i += skip_qoute_inside(str + i);
		else if (str[i] == '|' && a--)
		{
			if (!check_space_pipe(str + i))
				return (0);
			if ((str[i + 1] && str[i + 1] == '|')
				|| (str[i - 1] && str[i - 1] == '|'))
				a = 1;
		}
		else if (str[i] != ' ' && str[i] != '\n')
			a = 1;
	}
	return (a);
}

char	*ft_pipe(char *line)
{
	char	*str;
	int		a;

	a = !check_pipe(line, ft_strlen2(line));
	free(g_all.herd);
	g_all.herd = ft_strdup("pipe> ");
	while (a && !g_all.orand)
	{
		str = readline(g_all.herd);
		if (!str)
		{
			if (!g_all.no_init)
				ft_putstr_fd(SYNTAX_ERROR, 2);
			g_all.no_init = 1;
			free(line);
			free(str);
			return (NULL);
		}
		if (!check_line_pipe(str))
			return (NULL);
		line = ft_strjoin2(line, str, 1);
		a = !check_pipe(line, ft_strlen2(line));
	}
	return (line);
}

char	*check_full(char *line)
{
	int	v;
	int	a;

	if (!line)
		return (NULL);
	v = (!check_pipe(line, ft_strlen2(line)));
	if (!v)
		a = check_or_and(line);
	while (v || a == -1 || a == 0)
	{
		line = ft_pipe(line);
		line = ft_or_and(line);
		v = (!check_pipe(line, ft_strlen2(line)));
		if (!v)
			a = check_or_and(line);
		if (g_all.orand)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

char	*check_unclosed(char *arg)
{
	g_all.p = -1;
	if ((!check_pipe(arg, ft_strlen2(arg)) || !check_or_and(arg)
			|| check_or_and(arg) == -1) && !g_all.orand)
	{
		g_all.p = dup(0);
		arg = check_full(arg);
		dup(g_all.p);
		close(g_all.p);
	}
	g_all.p = -1;
	if (g_all.orand)
	{
		free(arg);
		return (NULL);
	}
	return (arg);
}
