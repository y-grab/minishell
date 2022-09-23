/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:00:31 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/26 17:00:15 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var2(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[i] != '_')
		return (0);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

void	ft_lstdel_from_list(t_lstk **lst, t_lstk *to_del)
{
	t_lstk	*tmp;

	tmp = *lst;
	if (*lst && *lst == to_del)
	{
		*lst = (*lst)->next;
		ft_lstdelone_key(tmp, free);
	}
	else if (*lst)
	{
		while (tmp->next)
		{
			if (tmp->next == to_del)
			{
				tmp->next = tmp->next->next;
				break ;
			}
			tmp = tmp->next;
		}
		ft_lstdelone_key(to_del, free);
	}
}

void	ft_unset2(char *cmd, int *res)
{
	t_lstk	*env;

	env = g_all.env;
	*res = !is_valid_var2(cmd);
	while (env && !*res)
	{
		if (!ft_strncmp(cmd, env->key, ft_strlen2(cmd))
			&& ft_strlen2(cmd) == ft_strlen2(env->key))
		{
			ft_lstdel_from_list(&g_all.env, env);
			return ;
		}
		env = env->next;
	}
	env = g_all.local;
	while (env && !*res)
	{
		if (!ft_strncmp(cmd, env->key, ft_strlen2(cmd))
			&& ft_strlen2(cmd) == ft_strlen2(env->key))
		{
			ft_lstdel_from_list(&g_all.local, env);
			return ;
		}
		env = env->next;
	}
}

int	ft_unset(char **cmd)
{
	int		i;
	int		res;

	i = -1;
	while (cmd && cmd[++i])
	{
		ft_unset2(cmd[i], &res);
		if (res)
			printf("%s: export: `%s': not a valid identifier\n",
				g_all.argv[0], cmd[i]);
		if (g_all.exit_code)
			g_all.exit_code = g_all.exit_code;
		else
			g_all.exit_code = res;
	}
	return (g_all.exit_code);
}
