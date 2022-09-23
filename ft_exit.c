/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:00:55 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 12:31:02 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **cmd)
{
	int	i;

	i = -1;
	if (!cmd[0])
	{
		printf("exit\n");
		exit(0);
	}
	while (cmd[0][++i])
	{
		if (!ft_isdigit(cmd[0][i]))
		{
			printf("exit: %s: numeric argument required\n", cmd[0]);
			exit(255);
		}
	}
	if (cmd[1])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	printf("exit\n");
	exit(ft_atoi(cmd[0]) % 256);
}

void	pr_error(void)
{
	ft_putstr_fd("Minishell : No such file or directory\n", 2);
	g_all.exit_code = 127;
}

char	*join_p(char *p, char **s_path, int i, char **str)
{
	p = ft_strjoin2(ft_strdup(s_path[i]), "/", 1);
	p = ft_strjoin2(p, *str, 1);
	return (p);
}

char	*del_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] != '\0')
			process_backslash(str, &i);
		i++;
	}
	return (str);
}
