/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:41:52 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 14:00:57 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

char	*change_wild(char *s)
{
	int		i;
	char	*new;

	i = -1;
	new = ft_strdup(s);
	while (new[++i])
		new[i] = new[i] * (new[i] != '*') - 4 * (new[i] == '*');
	return (new);
}

void	search_in_dir3(char *d, char **pfix_sfix, char **new_p_s, char **new_d)
{
	*new_d = ft_strjoin2(ft_strdup(d), "/", 1);
	*new_d = ft_strjoin2(*new_d, g_all.d_name, 1);
	new_p_s[0] = ft_strjoin2(ft_strdup(pfix_sfix[0]), g_all.d_name, 1);
	new_p_s[0] = ft_strjoin2(new_p_s[0], "/", 1);
	new_p_s[1] = pfix_sfix[1];
}

void	search_in_dir2(char *d, char **pfix_sfix, char **n_f, int l)
{
	char	*new_d;
	char	*new_p_s[2];

	search_in_dir3(d, pfix_sfix, new_p_s, &new_d);
	if (!n_f[l + 1] && (check_dir(new_d) || !pfix_sfix[1][0]))
	{
		if (n_f[0][0] == '.')
			pfix_sfix[0][ft_strlen2(pfix_sfix[0]) - 1] = 0;
		if (n_f[0][1] == '.')
			pfix_sfix[0][ft_strlen2(pfix_sfix[0]) - 1] = 0;
		g_all.line[g_all.line_c] = ft_strdup(pfix_sfix[0]);
		g_all.line[g_all.line_c] = ft_strjoin_free(g_all.line[g_all.line_c],
				ft_strdup(g_all.d_name));
		g_all.line[g_all.line_c] = ft_strjoin_free(g_all.line[g_all.line_c],
				ft_strdup(pfix_sfix[1]));
		g_all.line_c++;
		if (n_f[0][0] == '.')
			pfix_sfix[0][ft_strlen2(pfix_sfix[0])] = '.';
		if (n_f[0][1] == '.')
			pfix_sfix[0][ft_strlen2(pfix_sfix[0])] = '.';
	}
	else
		search_in_dir(new_d, new_p_s, n_f, l + 1);
	free(new_d);
	free(new_p_s[0]);
}

int	search_in_dir(char *d, char **pfix_sfix, char **n_f, int l)
{
	DIR				*dir;
	struct dirent	*p;
	char			*cng;

	dir = opendir(d);
	if (!dir)
		return (0);
	p = readdir(dir);
	while (p)
	{
		cng = change_wild(p->d_name);
		g_all.d_name = p->d_name;
		if (is_matching(cng, n_f[l]) && ((p->d_name[0] != '.'
					&& n_f[0][0] != '.') || n_f[0][0] == '.'))
			search_in_dir2(d, pfix_sfix, n_f, l);
		free(cng);
		g_all.d_name = NULL;
		p = readdir(dir);
	}
	closedir(dir);
	return (0);
}
