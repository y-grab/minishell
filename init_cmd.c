/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:05:32 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:24:18 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->use = 1;
	node->here_doc = NULL;
	node->rid = NULL;
	node->type = NULL;
	node->cmd = NULL;
	node->next = NULL;
	return (node);
}

void	init_data(char **s, int len)
{
	s[len] = NULL;
	while (len--)
		s[len] = NULL;
}

int	init_cmd_flag(t_cmd *cmd, int h_doc, int red, int cmnd)
{
	cmd->here_doc = (char **)malloc(sizeof(char *) * (h_doc + 1));
	cmd->rid = (char **)malloc(sizeof(char *) * (red + 1));
	cmd->type = (int *)malloc(sizeof(int) * (red + 1));
	cmd->cmd = (char **)malloc(sizeof(char *) * (cmnd + 1));
	if (!cmd->here_doc || !cmd->rid || !cmd->cmd || !cmd->type)
		return (0);
	init_data(cmd->here_doc, h_doc);
	init_data(cmd->rid, red);
	init_data(cmd->cmd, cmnd);
	g_all.cmd = cmnd;
	g_all.red = red;
	g_all.last_in = 0;
	return (1);
}

int	check_cmd_flag(t_cmd *cmd, char **s)
{
	int	h_doc;
	int	red;
	int	cmnd;
	int	i;

	h_doc = 0;
	red = 0;
	cmnd = 0;
	i = -1;
	while (s && s[++i])
	{
		red += ((s[i][0] == '>' && s[i][1] == '>')
				|| (s[i][0] == '<' && !s[i][1]) || s[i][0] == '>');
		h_doc += (s[i][0] == '<' && s[i][1] == '<');
		if (s[i][0] == '>' || s[i][0] == '<')
			i++;
		else
			cmnd++;
	}
	if (!cmnd)
		cmd->use = 0;
	return (init_cmd_flag(cmd, h_doc, red, cmnd));
}
