/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:49:12 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 12:06:34 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chaild_wait(int up_to)
{
	if (up_to)
	{
		waitpid(g_all.pid_cmd, &up_to, 0);
		if (WIFEXITED(up_to))
		g_all.exit_code = WEXITSTATUS(up_to);
		if (WTERMSIG(up_to) == SIGQUIT || WTERMSIG(up_to) == SIGINT)
		{
			g_all.exit_code = 128 + WTERMSIG(up_to);
			if (WTERMSIG(up_to) == SIGQUIT)
				ft_putendl_fd("Quit: 3", 1);
			if (WTERMSIG(up_to) == SIGINT)
				ft_putstr_fd("\n", 1);
		}
		up_to = !g_all.exit_code;
	}
	return (up_to);
}

int	check_blt(char *cmd)
{
	int		i;
	char	*str[8];

	str[0] = "echo";
	str[1] = "env";
	str[2] = "cd";
	str[3] = "pwd";
	str[4] = "unset";
	str[5] = "exit";
	str[6] = "export";
	str[7] = NULL;
	i = -1;
	while (cmd && str[++i])
		if (!ft_strncmp(cmd, str[i], ft_strlen2(str[0]) + 1))
			return (1);
	return (0);
}

int	exec_blt(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd[0])
		return (0);
	if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (ft_cd(cmd->cmd[1]));
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (ft_echo(&cmd->cmd[1], cmd->out));
	if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (ft_pwd(cmd->cmd[1], cmd->out));
	if (!ft_strncmp(cmd->cmd[0], "env", 4))
		return (ft_env(cmd->cmd[1], cmd->out));
	if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		return (ft_exit(&cmd->cmd[1]));
	if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		return (ft_unset(&cmd->cmd[1]));
	if (!ft_strncmp(cmd->cmd[0], "export", 7))
		return (ft_export(&cmd->cmd[1], &g_all.env, cmd->out, 3)
			|| ft_export(&cmd->cmd[1], &g_all.local, cmd->out, 2));
	return (g_all.exit_code);
}

int	print_check_error(char *str)
{
	ft_putstr_fd("Minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_all.exit_code = 127;
	return (0);
}

int	check_path(char **str, t_lstk *path)
{
	int		i;
	char	**s_path;
	char	*p;

	i = -1;
	if (!path)
	{
		pr_error();
		return (0);
	}
	s_path = ft_split(path->content, ':');
	while (s_path[++i])
	{
		p = join_p(p, s_path, i, str);
		if (access(p, X_OK) != -1)
		{
			free(*str);
			*str = p;
			return (1);
		}
		free(p);
	}
	ft_free(s_path);
	print_check_error(*str);
	return (0);
}
