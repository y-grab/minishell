/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:44:24 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 11:14:53 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_backslash(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(str);
	free(tmp);
	free(tmp2);
	return (tmp3);
}

int	is_bslash(char *s, int i)
{
	int	count;

	count = 0;
	while (i > 0 && s[i - 1] == '\\')
	{
		count++;
		i--;
	}
	return (count % 2);
}

void	syn_error_qoutes(char *str, int i, int *sq, int *dq)
{
	if (str[i] == '\"' && *sq < 0)
		*dq *= 1;
	else if (str[i] == '\"' && (i == 0 || !is_bslash(str, i)))
		*dq *= -1;
	else if (str[i] == '\'')
	{
		if (*dq > 0 && *sq < 0)
			*sq *= -1;
		else if (*dq > 0 && *sq > 0 && (i == 0 || !is_bslash(str, i)))
			*sq *= -1;
	}
}

int	syn_backslash_exit(void)
{
	write(2, "backslash not supported\n", \
	ft_strlen("backslash not supported\n"));
	return (1);
}

int	syn_error_util(char *str, char a, int *sq, int *dq)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		syn_error_qoutes(str, i, sq, dq);
		if ((str[i] == a) && *dq > 0 && *sq > 0)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == a || (!str[i] && a == '|'))
				return (-1);
		}
	}
	return (1);
}
