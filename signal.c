/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:28:02 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:15:39 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_line(void)
{
	int	i;
	int	last;
	int	new;

	i = -1;
	last = 0;
	new = 0;
	while (rl_line_buffer[++i])
	{
		if (rl_line_buffer[i] == '\n')
		{
			last = new;
			new = i + 1;
		}
	}
	return (last);
}

void	signal_child(int sign)
{
	if (sign == SIGQUIT && g_all.pid_cmd == 0)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_all.exit_code = 131;
	}
	else if (sign == SIGINT && g_all.pid_cmd == 0)
	{
		ft_putchar_fd('\n', 1);
		g_all.exit_code = 130;
	}
}

void	signals_handler(int sign)
{
	if (g_all.p != -1 && g_all.p != -2 && sign == SIGINT)
	{
		g_all.exit_code = 130;
		g_all.no_init = 1;
		printf("\r");
		printf("%s%s  \n", g_all.herd, rl_line_buffer);
		rl_redisplay();
		close(0);
	}
	else
	{
		g_all.exit_code = 1;
		if (last_line() && !g_all.no_init)
			printf("\r%s  ", &rl_line_buffer[last_line() + 1]);
		else if (!g_all.no_init)
			printf("\rMinishell : %s  ", rl_line_buffer);
		if (!g_all.no_init)
			printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
