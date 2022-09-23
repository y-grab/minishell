/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:31:26 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 21:23:30 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_norm(char *line, int *i, int *a, int *check)
{
	if (line[*i] == '\"' || line[*i] == '\'')
		*i += skip_qoute_inside(line + *i);
	else if (line[*i + 1] && ((line[*i] == '&' && line[*i + 1] == '&')
			|| (line[*i] == '|' && line[*i + 1] == '|')))
	{
		line[*i] = '\0';
		if ((!g_all.exit_code && *check == 1)
			|| (g_all.exit_code && *check == 2) || !*a)
			executor2((line + *a));
		*check = (line[*i + 1] == '&') + 2 * (line[*i + 1] == '|');
		*a = ++(*i) + 1;
	}
}

int	pars(t_cmd **cmd, char **splt)
{
	t_cmd	*new;

	new = init_cmd();
	if (pars_error(splt) || !check_cmd_flag(new, splt))
	{
		ft_free(splt);
		return (1);
	}
	init_new_cmd(new, splt);
	add_back_node(cmd, new);
	g_all.nb_cmd++;
	ft_free(splt);
	return (0);
}

t_cmd	*parsing(char *line)
{
	int		i;
	char	**s;
	t_cmd	*cmd;

	cmd = NULL;
	if (!line)
		return (NULL);
	i = -1;
	s = ft_split_shell(line, '|');
	while (s && s[++i])
	{
		s[i] = change_line(s[i]);
		if (pars(&cmd, ft_split_shell(s[i], ' ')))
		{
			ft_free_list(&cmd);
			ft_free(s);
			g_all.exit_code = 258;
			return (NULL);
		}
	}
	ft_free(s);
	return (cmd);
}

void	executor2(char *line)
{
	t_cmd	*cmd;

	cmd = parsing(line);
	if (cmd && !define_cmd(cmd))
		g_all.exit_code = execution(cmd);
	ft_free_list(&cmd);
}

void	executor(char	*line)
{
	int	i;
	int	a;
	int	check;
	int	lent;

	a = 0;
	i = 0;
	check = 1;
	if (!line)
		return ;
	lent = ft_strlen2(line);
	del_brackets(line);
	while (i < lent)
	{
		a = i;
		while (line[i])
		{
			ft_norm(line, &i, &a, &check);
			i++;
		}
	}
	if ((!g_all.exit_code && check == 1) || (g_all.exit_code && check == 2)
		|| !a)
		executor2((line + a));
}
