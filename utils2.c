/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:51:48 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/30 21:06:44 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_cmd **lst)
{
	t_cmd	*tmp;

	while (lst && *lst)
	{
		tmp = *lst;
		ft_free(tmp->here_doc);
		ft_free(tmp->rid);
		ft_free(tmp->cmd);
		free(tmp->type);
		*lst = (*lst)->next;
		free(tmp);
	}
}

void	clear_line(char *arg)
{
	int		i;
	int		j;
	char	in_quote;

	i = -1;
	j = 0;
	if (!arg)
		return ;
	while (++i < ft_strlen2(arg))
	{
		if (arg[i] == '\"' || arg[i] == '\'')
		{
			in_quote = arg[i];
			while (++i < ft_strlen2(arg) && in_quote != arg[i])
				arg[j++] = arg[i];
		}
		else if (arg[i] != '$' || (arg[i + 1] != '\"' && arg[i + 1] != '\''))
			arg[j++] = arg[i];
	}
	arg[j] = '\0';
}

int	in_file(t_cmd *cmd, char *s)
{
	if (cmd->in && !g_all.last_in)
		close(cmd->in);
	if (!s || s[0] == -3)
		return (errors_return_red(&s[1], cmd));
	if (!g_all.last_in)
	{
		cmd->in = open(s, O_RDONLY);
		if (cmd->in == -1)
		{
			cmd->use = 0;
			return (errors_return(s));
		}
	}
	else if (open(s, O_RDONLY) == -1)
	{
		cmd->use = 0;
		return (errors_return(s));
	}
	return (0);
}

int	appand_file(t_cmd *cmd, char *s)
{
	if (cmd->out != 1)
		close(cmd->out);
	if (!s || s[0] == -3)
		return (errors_return_red(&s[1], cmd));
	cmd->out = open(s, O_APPEND | O_WRONLY | O_CREAT, 0666);
	if (cmd->out == -1)
		return (errors_return(s));
	return (0);
}

int	out_file(t_cmd *cmd, char *s)
{
	if (cmd->out != 1)
		close(cmd->out);
	if (!s || s[0] == -3)
		return (errors_return_red(&s[1], cmd));
	cmd->out = open(s, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (cmd->out == -1)
		return (errors_return(s));
	return (0);
}
