/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:55:29 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/27 16:47:21 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(t_cmd *cmd)
{
	int	p[2];

	cmd->in = 0;
	while (cmd->next)
	{
		if (pipe(p) == -1)
			return (errors_return("pipe"));
		cmd->out = p[1];
		cmd->next->in = p[0];
		cmd = cmd->next;
	}
	cmd->out = 1;
	return (0);
}

int	read_from_here_doc(t_cmd *cmd)
{
	int	i;

	while (cmd && g_all.p == -1)
	{
		i = -1;
		while (cmd->here_doc[++i] && g_all.p == -1)
			here_doc(cmd, cmd->here_doc[i]);
		cmd = cmd->next;
	}
	g_all.p = -1;
	return (g_all.exit_code);
}

int	open_files(t_cmd *cmd, int (*t[4])(t_cmd *, char *))
{
	int	i;

	while (cmd && g_all.p == -1 && !g_all.exit_code)
	{
		i = -1;
		while (cmd->rid[++i] && g_all.p == -1 && !g_all.exit_code)
			t[cmd->type[i]](cmd, cmd->rid[i]);
		cmd = cmd->next;
	}
	g_all.exit_code = !!g_all.exit_code;
	return (0);
}

int	define_cmd(t_cmd *cmd)
{
	int	(*t[4])(t_cmd *, char *);

	g_all.p = -1;
	t[1] = in_file;
	t[2] = out_file;
	t[3] = appand_file;
	g_all.exit_code = 0;
	if (open_pipes(cmd))
		return (g_all.exit_code);
	if (read_from_here_doc(cmd))
		return (g_all.exit_code);
	if (open_files(cmd, t))
		return (g_all.exit_code);
	return (g_all.exit_code);
}
