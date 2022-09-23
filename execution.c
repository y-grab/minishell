/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:36:20 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 11:39:57 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_str(t_lstk *lst)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_calloc(ft_lstsize_key(lst) + 1, sizeof(char *));
	while (lst)
	{
		str[i] = ft_strjoin2(ft_strdup(lst->key), "=", 1);
		str[i] = ft_strjoin2(str[i], lst->content, 1);
		lst = lst->next;
		i++;
	}
	return (str);
}

void	close_all(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->in)
			close(cmd->in);
		if (cmd->out != 1)
			close(cmd->out);
		cmd = cmd->next;
	}
}

void	exec_cmd(t_cmd *cmd, t_cmd *cmd2)
{
	signal(SIGINT, SIG_IGN);
	g_all.pid_cmd = fork();
	if (g_all.pid_cmd == 0)
	{
		g_all.pid = 1;
		signal(SIGINT, signal_child);
		signal(SIGQUIT, signal_child);
		dup2(cmd->in, 0);
		dup2(cmd->out, 1);
		close_all(cmd2);
		if (ft_strchr(cmd->cmd[0], '/')
			|| check_path(&cmd->cmd[0], find_key2("PATH", g_all.env)))
		{
			if (execve(cmd->cmd[0], cmd->cmd, g_all.exec_envp) == -1
				&& !check_path(&cmd->cmd[0], find_key2("PATH", g_all.env)))
				exit(127);
			else if (execve(cmd->cmd[0], cmd->cmd, g_all.exec_envp) == -1)
				exit(errors_return(cmd->cmd[0]));
		}
		else
			exit (127);
	}
}

int	exec_cmds(t_cmd *cmd, t_cmd *cmd2)
{
	int	up_to;

	up_to = 1;
	while (cmd)
	{
		if (cmd->use && cmd->cmd[0] && cmd->cmd[0][0])
			exec_cmd(cmd, cmd2);
		else if (cmd->use && cmd->cmd[0] && !cmd->cmd[0][0])
		{
			ft_putstr_fd("Minishell : command not found\n", 2);
			g_all.exit_code = 127;
		}
		if (!cmd->next && !cmd->use)
			up_to = 0;
		cmd = cmd->next;
	}
	return (up_to);
}

int	execution(t_cmd *cmd)
{
	int	up_to;

	g_all.p = -2;
	up_to = 0;
	ft_free(g_all.exec_envp);
	g_all.exec_envp = list_to_str(g_all.env);
	if (g_all.nb_cmd == 1 && cmd->use && check_blt(cmd->cmd[0]))
		g_all.exit_code = exec_blt(cmd);
	else
		up_to = exec_cmds(cmd, cmd);
	close_all(cmd);
	up_to = chaild_wait(up_to);
	while (wait(NULL) != -1)
		;
	sigaction(SIGINT, &g_all.sig, NULL);
	signal(SIGQUIT, SIG_IGN);
	g_all.p = -1;
	return (((g_all.exit_code / 256) * up_to) + (g_all.exit_code * !up_to));
}
