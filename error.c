/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:57:46 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 14:10:17 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_error(char c)
{
	if (!g_all.orand)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	g_all.exit_code = 258;
	g_all.orand = 1;
}

int	errors_print(char *s)
{
	if (s)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(&g_all.argv[0][2], 2);
		ft_putstr_fd(": parse error near `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(&g_all.argv[0][2], 2);
		ft_putstr_fd(": parse error near `newline'\n", 2);
	}
	return (1);
}

int	pars_error(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!s[i + 1] && (s[i][0] == '>' || s[i][0] == '<'))
			return (errors_print(s[i + 1]));
		else if ((s[i][0] == '>' || s[i][0] == '<')
			&& (s[i + 1][0] == '>' || s[i + 1][0] == '<'))
			return (errors_print(s[i + 1]));
	}
	return (0);
}

int	errors_return_red(char *s, t_cmd *cmd)
{
	ft_putstr_fd("  ", 2);
	ft_putstr_fd(&g_all.argv[0][2], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	cmd->use = 0;
	g_all.exit_code = 1;
	return (1);
}

int	errors_return(char *s)
{
	char	*er;

	er = strerror(errno);
	g_all.exit_code = errno;
	ft_putstr_fd("", 2);
	ft_putstr_fd(&g_all.argv[0][2], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(er, 2);
	ft_putstr_fd("\n", 2);
	return (g_all.exit_code);
}
