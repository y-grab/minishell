/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_new_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujicama <ujicama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:46:12 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 19:31:44 by ujicama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_quote2(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] != -2)
			str[j++] = str[i++];
		else
			i++;
	}
	if (str)
		str[j] = '\0';
	return (str);
}

void	insert_cmd_h(t_cmd *new, char **s, int *i, int *h)
{
	new->t_type = (ft_strchr(s[++(*i)], '\'') || ft_strchr(s[(*i)], '\"'));
	clear_line(s[(*i)]);
	new->here_doc[(*h)++] = del_quote(ft_strdup(s[(*i)]));
	g_all.last_in = 1;
}

void	insert_cmd_r(t_cmd *new, char **s, int *r, int *i)
{
	new->type[(*r)] = (s[(*i)][0] == '<')
		+ 2 * (s[(*i)][0] == '>' && !s[(*i)][1])
		+ 3 * (s[(*i)][0] == '>' && s[(*i)][1] == '>');
	new->rid[(*r)++] = del_quote2(del_quote
			(handle_dollar(ft_strdup(s[++(*i)]))));
	if (!new->rid[(*r) - 1] || !new->rid[(*r) - 1][0])
	{
		free(new->rid[(*r) - 1]);
		new->rid[(*r) - 1] = ft_strdup(" ");
		new->rid[(*r) - 1][0] = -3;
		new->rid[(*r) - 1] = ft_strjoin3(new->rid[(*r) - 1], s[(*i)], 1);
	}
	wildcard(del_quote(change_wildcard2(s[(*i)])));
	if (g_all.line_c)
	{
		free(new->rid[(*r) - 1]);
		new->rid[(*r) - 1] = NULL;
		new->rid = ft_strdoublejoin(&(new->rid),
				g_all.line, g_all.red, g_all.line_c);
		(*r) = ft_double_strlen(new->rid);
		g_all.line_c = 0;
	}
	g_all.last_in = 0;
}

void	insert_cmd_c(t_cmd *new, char **s, int *c, int *i)
{
	new->cmd[(*c)] = del_quote2(del_quote(handle_dollar(ft_strdup(s[(*i)]))));
	new->cmd[(*c)++] = parser(new->cmd[(*c)]);
	if (!ft_strrchr(s[(*i)], '\"') && !ft_strrchr(s[(*i)], '\'')
		&& (!new->cmd[(*c) - 1] || !new->cmd[(*c) - 1][0]))
	{
		free(new->cmd[--(*c)]);
		new->cmd[(*c)] = NULL;
	}
	wildcard(del_quote(change_wildcard2(s[(*i)])));
	if (g_all.line_c)
	{
		free(new->cmd[(*c) - 1]);
		new->cmd[(*c) - 1] = NULL;
		new->cmd = ft_strdoublejoin(&(new->cmd),
				g_all.line, g_all.cmd, g_all.line_c);
		(*c) = ft_double_strlen(new->cmd);
		g_all.line_c = 0;
	}
}

void	init_new_cmd(t_cmd *new, char **s)
{
	int	h;
	int	r;
	int	c;
	int	i;

	h = 0;
	r = 0;
	c = 0;
	i = -1;
	while (s && s[++i])
	{
		if (s[i][0] == '<' && s[i][1] == '<')
			insert_cmd_h(new, s, &i, &h);
		else if ((s[i][0] == '>' || s[i][0] == '<'))
			insert_cmd_r(new, s, &r, &i);
		else
			insert_cmd_c(new, s, &c, &i);
	}
}
