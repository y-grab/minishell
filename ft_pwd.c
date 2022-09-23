/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:00:02 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:17:28 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(void)
{
	ft_putstr_fd("pwd: too many arguments\n", 2);
	g_all.exit_code = 1;
	return (1);
}

int	ft_pwd(char *p, int fd_out)
{
	char	*s;
	t_lstk	*l;

	(void) p;
	s = getcwd(NULL, 0);
	if (s)
	{
		ft_putstr_fd(s, fd_out);
		ft_putstr_fd("\n", fd_out);
	}
	else
	{
		l = find_key2("PWD", g_all.env);
		if (l)
		{
			ft_putstr_fd(l->content, fd_out);
			ft_putstr_fd("\n", fd_out);
		}
		return (1);
	}
	free(s);
	return (0);
}
