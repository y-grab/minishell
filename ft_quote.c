/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:31:06 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 21:35:23 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_quote(char *str)
{
	int	quote;
	int	in_expanded;
	int	i;
	int	j;

	i = -1;
	j = 0;
	quote = 0;
	in_expanded = 0;
	while (str && str[++i])
	{
		if (str[i] == -2)
		{
			in_expanded = !in_expanded;
			str[j++] = str[i];
		}
		else if ((((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\' )
				|| str[i] == -2) && (str[i] == quote || !quote) && !in_expanded)
			quote = str[i] * !quote;
		else
			str[j++] = str[i];
	}
	if (str)
		str[j] = '\0';
	return (str);
}
