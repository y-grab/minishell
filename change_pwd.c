/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:16:14 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:25:02 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(void)
{
	char	*e[2];

	e[0] = ft_strjoin3(ft_strdup("PWD="), getcwd(NULL, 0), 1);
	e[1] = NULL;
	ft_export(e, &g_all.env, 1, 3);
	free(e[0]);
}

void	change_old_pwd(char *s)
{
	char	*e[2];

	e[0] = ft_strjoin3(ft_strdup("OLDPWD="), s, 1);
	e[1] = NULL;
	ft_export(e, &g_all.env, 1, 3);
	free (e[0]);
}
