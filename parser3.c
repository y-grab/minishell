/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:32:29 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 12:20:04 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syn_error_check(char *str, char a)
{
	int		i;
	int		sq;
	int		dq;

	sq = 1;
	dq = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && ft_strchr(SEP, str[i]))
		i++;
	if (str[i] == a || syn_error_util(str, a, &sq, &dq) < 0)
	{
		ft_putstr_fd("Minishell : syntax error\n", 2);
		return (-1);
	}
	if (dq == -1 || sq == -1)
	{
		ft_putstr_fd("Minishell : quote error\n", 2);
		return (-1);
	}
	return (0);
}
