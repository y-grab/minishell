/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:46:51 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/25 17:40:39 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_norm5(int *i, char *l, int *in_dquote)
{
	if (l[*i] == '\"')
		*in_dquote = -1 * !*in_dquote;
	if (l[*i] == '\'' && !*in_dquote)
		*in_dquote = 1;
	if (l[*i] && *in_dquote && *in_dquote != -1)
	{
		while (l[++(*i)] && l[*i] != '\'')
			;
		*in_dquote = 0;
	}
}

char	*find_key(char *key, t_lstk *env)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, strlen(env->key) + 1))
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*handle_dollar2(char *l)
{
	char	*line;
	int		i;
	int		left;

	left = 0;
	i = -1;
	line = NULL;
	while (l && l[++i])
	{
		if (l[i] == '$' && ft_isdigit(l[i + 1]))
			f1(&line, l, &left, &i);
		else if (l[i] == '$' && l[i + 1] == '?')
			f2(&line, l, &left, &i);
		else if (l[i] == '$' && (l[i + 1] == '_' || ft_isalpha(l[i + 1])))
			f3(&line, l, &left, &i);
	}
	line = ft_strjoin3(line, ft_substr(l, left, i - left), 1);
	free(l);
	return (line);
}
