/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:59:50 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 12:21:49 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_here(char *s)
{
	printf("%s: cd: %s: %s\n", g_all.argv[0], s, strerror(errno));
	g_all.exit_code = 1;
}

int	handle_tilde(char *path, char *ss)
{
	t_lstk	*s;

	if (!path || (path[0] == '~' && !path[1]))
	{
		s = find_key2("HOME", g_all.env);
		if (s && chdir(s->content) == -1)
		{
			printf("%s: cd: %s: %s\n", g_all.argv[0], \
			(char *) s->content, strerror(errno));
			g_all.exit_code = 1;
			free(ss);
			return (1);
		}
		change_old_pwd(ss);
		change_pwd();
		return (1);
	}
	return (0);
}

int	handle_minus(char *path, char *ss)
{
	t_lstk	*s;

	if (path[0] == '-' && !path[1])
	{
		s = find_key2("OLDPWD", g_all.env);
		if (s && chdir(s->content) == -1)
		{
			print_here(s->content);
			free(ss);
			return (1);
		}
		else if (!s)
		{
			printf("%s: cd: OLDPWD not set\n", g_all.argv[0]);
			g_all.exit_code = 1;
			free(ss);
			return (1);
		}
		printf("%s\n", (char *) s->content);
		change_old_pwd(ss);
		change_pwd();
		return (1);
	}
	return (0);
}

int	handle_dot(char *path, char *ss)
{
	char	*pwd;

	if (path[0] == '.' && !path[1])
	{
		pwd = getcwd(NULL, 0);
		if (!ft_strncmp(path, ".", 2) && !pwd)
		{
			print_here2();
			g_all.exit_code = 0;
			free(ss);
			free(pwd);
			return (1);
		}
		else if (!pwd)
		{
			free(pwd);
			return (1);
		}
		free(pwd);
	}
	return (0);
}

int	ft_cd(char *path)
{
	char	*pwd;

	g_all.exit_code = 0;
	pwd = getcwd(NULL, 0);
	if (handle_tilde(path, pwd))
		return (g_all.exit_code);
	if (handle_minus(path, pwd))
		return (g_all.exit_code);
	if (handle_dot(path, pwd))
		return (g_all.exit_code);
	if (chdir(path) == -1)
	{
		printf("%s: cd: %s: %s\n", g_all.argv[0], path, strerror(errno));
		free(pwd);
		g_all.exit_code = 1;
		return (1);
	}
	change_pwd();
	change_old_pwd(pwd);
	return (g_all.exit_code);
}
