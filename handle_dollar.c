/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:46:09 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 21:39:05 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f1(char **line, char *l, int *ll, int *r)
{
	int		i;
	int		left;
	char	*tmp;

	left = *ll;
	i = *r;
	tmp = ft_strdup(" ");
	tmp[0] = -2;
	*line = ft_strjoin_free(*line, ft_substr(l, left, i - left));
	*line = ft_strjoin_free(*line, ft_strdup(tmp));
	if (l[i + 1] == '0')
		*line = ft_strjoin3(*line, &g_all.argv[0][2], 1);
	left = ++i + 1;
	*r = i;
	*ll = left;
	*line = ft_strjoin_free(*line, ft_strdup(tmp));
	free(tmp);
}

void	f2(char **line, char *l, int *ll, int *r)
{
	int		i;
	int		left;
	char	*tmp;

	i = *r;
	left = *ll;
	tmp = ft_strdup(" ");
	tmp[0] = -2;
	*line = ft_strjoin_free(*line, ft_substr(l, left, i - left));
	*line = ft_strjoin_free(*line, ft_strdup(tmp));
	*line = ft_strjoin_free(*line, ft_itoa(g_all.exit_code));
	*line = ft_strjoin_free(*line, ft_strdup(tmp));
	left = ++i + 1;
	*r = i;
	*ll = left;
	free(tmp);
}

void	f3(char **line, char *l, int *ll, int *r)
{
	int		i;
	int		left;
	char	*tmp;

	left = *ll;
	i = *r;
	*line = ft_strjoin_free(*line, ft_substr(l, left, i - left));
	left = ++i;
	tmp = ft_strdup(" ");
	tmp[0] = -2;
	*line = ft_strjoin_free(*line, ft_strdup(tmp));
	free(tmp);
	while (l[i] && ft_isalnum(l[i]))
		i++;
	tmp = ft_substr(l, left, i - left);
	*line = ft_strjoin_free(*line, find_key(tmp, g_all.env));
	left = i;
	i--;
	*r = i;
	*ll = left;
	free(tmp);
	tmp = ft_strdup(" ");
	tmp[0] = -2;
	*line = ft_strjoin_free(*line, ft_strdup(tmp));
	free(tmp);
}

static void	ft_norm(int *i, int *left, int *in_dquote)
{
	*in_dquote = 0;
	*left = 0;
	*i = -1;
}

char	*handle_dollar(char *l)
{
	char	*line;
	int		i;
	int		left;
	int		in_dquote;

	line = NULL;
	ft_norm(&i, &left, &in_dquote);
	while (l && l[++i])
	{
		ft_norm5(&i, l, &in_dquote);
		if ((l[i] == '\\') && (l[i + 1] == '$'))
			return (l);
		else if (l[i] == '$' && ft_isdigit(l[i + 1]))
			f1(&line, l, &left, &i);
		else if (l[i] == '$' && l[i + 1] == '?')
			f2(&line, l, &left, &i);
		else if (l[i] == '$' && ft_isalpha(l[i + 1]))
			f3(&line, l, &left, &i);
	}
	line = ft_strjoin_free(line, ft_substr(l, left, i - left));
	free(l);
	return (line);
}
