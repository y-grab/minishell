/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:00:14 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 12:06:59 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export(int fd)
{
	char	**str;
	int		i;

	i = -1;
	str = env_to_str(g_all.local);
	ft_sort_arry(str);
	while (str[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(str[i], fd);
		ft_putstr_fd("\n", fd);
	}
	ft_free(str);
	return (0);
}

t_lstk	*find_key2(char *key, t_lstk *env)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen2(env->key) + 1))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	check_arg_env(char *s, int flag)
{
	int	i;
	int	p_m;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		printf("Minishell : export: `%s': not a valid identifier\n", s);
		return (0);
	}
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (!s[i])
		return (flag);
	if (s[i] == '+' && s[i + 1] == '=')
		return (1);
	if (s[i] == '=')
		return (2);
	printf("Minishell : export: `");
	p_m = (s[i] == '=');
	i = 0;
	while (s[i] && ((s[i] != '=' && p_m) || !p_m))
		printf("%c", s[i++]);
	printf("': not a valid identifier\n");
	return (0);
}

void	ft_export2(char *cmd, t_lstk **envp, int *type, int flag)
{
	t_lstk	*node;
	int		p;

	node = NULL;
	*type = check_arg_env(cmd, flag);
	if (*type && *type < 3)
	{
		p = find_equal(cmd);
		cmd[p - (*type == 1)] = 0;
		node = find_key2(cmd, *envp);
	}
	if (!node && *type < 3)
		ft_lstadd_back_key(envp, ft_lstnew_key(ft_strdup(cmd), \
		ft_strdup(&cmd[p + 1])));
	else if (*type == 1 && node)
		node->content = ft_strjoin2(node->content, &cmd[p + 1], 1);
	else if (*type == 2 && node)
	{
		free(node->content);
		node->content = ft_strdup(&cmd[p + 1]);
	}
	if (*type && *type < 3)
		cmd[p - (*type == 1)] = '=' * (*type == 2) + '+' * (*type == 1);
}

int	ft_export(char **cmd, t_lstk **envp, int fd, int flag)
{
	int	i;
	int	type;
	int	ret;

	i = -1;
	ret = 0;
	if (!cmd[0] && flag == 2)
		return (print_export(fd));
	while (cmd && cmd[++i])
	{
		ft_export2(cmd[i], envp, &type, flag);
		if (!type)
			ret += 1;
		else
			ret += 0;
	}
	if (ret != 0)
		return (1);
	return (0);
}
