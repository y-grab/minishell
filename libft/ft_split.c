/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:03:02 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 13:35:11 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	unsigned int	words;
	unsigned int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			words++;
		while (s[i] != c && s[i])
			i++;
	}
	return (words);
}

static char	*ft_one_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	len;
	char			*word ;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	len = i;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_fill_words(char **dest, char const *s,
		char c, unsigned int words)
{
	unsigned int	i;

	dest = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		dest[i] = ft_one_word(s, c);
		if (!(dest[i]))
		{
			while (i > 0)
				free(dest[i--]);
			free(dest);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
	}
	dest[i] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char			**dest;
	unsigned int	words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	dest = NULL;
	dest = ft_fill_words(dest, s, c, words);
	return (dest);
}
