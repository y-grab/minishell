/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:01:36 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 13:32:42 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_main3(char *arg)
{
	g_all.no_init = 0;
	if (arg && arg[0])
	{
		valid_brackets(arg);
		arg = check_unclosed(arg);
	}
	if (arg && arg[0] && ft_strcmp(g_all.old_arg, arg))
	{
		free(g_all.old_arg);
		g_all.old_arg = ft_strdup(arg);
		add_history(arg);
	}
	if (!g_all.orand)
	{
		if (syn_error_check(arg, ';') < 0 || syn_backslash(arg))
		{
			free(arg);
			return (NULL);
		}
	}
	executor(arg);
	return (arg);
}

void	ft_main2(char *arg)
{
	while (1)
	{
		g_all.orand = 0;
		g_all.nb_cmd = 0;
		g_all.p = -1;
		arg = readline("Minishell : ");
		if (!arg)
		{
			printf("exit\n");
			exit(0);
		}
		arg = ft_main3(arg);
		free(arg);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*arg;

	(void)argc;
	arg = NULL;
	g_all.argv = argv;
	copy_env(envp);
	g_all.sig.sa_handler = signals_handler;
	g_all.sig.sa_flags = 0;
	sigaction(SIGINT, &g_all.sig, NULL);
	signal(SIGQUIT, SIG_IGN);
	ft_main2(arg);
	return (0);
}
