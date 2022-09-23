/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:47:46 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:20:18 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_str(t_lstk *lst)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_calloc(ft_lstsize_key(lst) + 1, sizeof(char *));
	while (lst)
	{
		str[i] = ft_strjoin2(ft_strdup(lst->key), "=\"", 1);
		str[i] = ft_strjoin2(str[i], lst->content, 1);
		str[i] = ft_strjoin2(str[i], "\"", 1);
		lst = lst->next;
		i++;
	}
	return (str);
}

void	ft_sort_arry(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env && env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_free(char **s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
}

t_cmd	*ft_nodelast(t_cmd *head)
{
	if (!head)
		return (head);
	if (!head->next)
		return (head);
	return (ft_nodelast(head->next));
}

void	add_back_node(t_cmd **head, t_cmd *new)
{
	if (!*head)
		*head = new;
	else
		ft_nodelast(*head)->next = new;
}
