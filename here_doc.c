/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:04:14 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:24:45 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_strings(char *s1, char *s2, int lent, char fin)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!fin && !s1[i] && !s2[i] && i == lent)
		return (1);
	if (fin && s1[i] == '\n' && i == lent)
		return (1);
	return (0);
}

void	red_here_doc(t_cmd *cmd, char *limiter, int *p)
{
	int		cont;
	char	*line;

	line = NULL;
	cont = 0;
	while (cont == 0)
	{
		line = readline(g_all.herd);
		if (line)
			cont = match_strings(line, limiter, ft_strlen2(limiter), 0);
		else
		{
			g_all.no_init = 1;
			free(line);
			break ;
		}
		if (!cmd->t_type)
			line = del_quote2(handle_dollar2(line));
		if (cont == 0)
		{
			write(p[1], line, ft_strlen2(line));
			write(p[1], "\n", 1);
		}
		free(line);
	}
}

int	here_doc(t_cmd *cmd, char *limiter)
{
	int	i;
	int	p[2];

	g_all.p = dup(0);
	pipe(p);
	if (cmd->in)
		close(cmd->in);
	cmd->in = p[0];
	free(g_all.herd);
	g_all.herd = ft_strdup("");
	g_all.heredoc = 1;
	i = -1;
	while (++i < g_all.nb_cmd - 1)
		g_all.herd = ft_strjoin_free(g_all.herd, ft_strdup("pipe "));
	g_all.herd = ft_strjoin_free(g_all.herd, ft_strdup("heredoc> "));
	red_here_doc(cmd, limiter, p);
	close(p[1]);
	dup(g_all.p);
	close(g_all.p);
	g_all.p = -1 * !g_all.no_init;
	return (g_all.exit_code);
}
