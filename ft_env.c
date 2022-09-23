/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:00:44 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/30 18:44:59 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **envp)
{
	ft_export(envp, &g_all.env, 1, 3);
	ft_export(envp, &g_all.local, 1, 2);
}

int	find_equal(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (s[i] == '=')
			return (i);
	return (i);
}

int	ft_env(char *s, int fd_out)
{
	int			i;
	char		**str;

	str = list_to_str(g_all.env);
	if (s)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_all.exit_code = 1;
		ft_free(str);
		return (1);
	}
	i = -1;
	while (str && str[++i])
	{
		ft_putstr_fd(str[i], fd_out);
		ft_putstr_fd("\n", fd_out);
	}
	ft_free(str);
	return (0);
}
