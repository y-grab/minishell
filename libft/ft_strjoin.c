/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:04:33 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/29 17:02:34 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	dest = (char *)malloc(i + j + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin2(char *s1, char *s2, int flag)
{
	size_t		i;
	size_t		j;
	char		*dest;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (NULL);
	dest = (char *)malloc(ft_strlen2(s1) + ft_strlen2(s2) + 2);
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		dest[i] = s1[i];
	if (!flag && s1[0] != '\0')
		dest[i++] = '\n';
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}

char	*ft_strjoin3(char *s1, char *s2, int type)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	str = (char *)malloc(ft_strlen2(s1) + ft_strlen2(s2) + 2);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	if (type == 0 && s1[0] != '\0')
		str[i++] = '\n';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
