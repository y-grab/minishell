/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:43:15 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/01 11:12:59 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_gnl(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

int	find_new_line(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\n')
			return (i);
	return (-1);
}

char	*read_buff(int fd, char **buff)
{
	int		end;
	int		bol;
	char	*res;

	bol = 1;
	while (bol)
	{
		res = (char *)malloc(BUFFER_SIZE + 1);
		if (!res)
			return (ft_free_gnl(buff));
		end = read(fd, res, BUFFER_SIZE);
		if (!end || end == -1)
			return (ft_free_gnl(&res));
		res[end] = 0;
		bol = (find_new_line(res) == -1);
		*buff = ft_strjoin_gnl(*buff, res);
		res = NULL;
	}
	return (*buff);
}

char	*read_line(int fd, char **buff)
{
	int		end;
	char	*line;

	line = NULL;
	end = find_new_line(*buff);
	if (end == -1)
	{
		read_buff(fd, buff);
		end = find_new_line(*buff);
	}
	if (end != -1)
	{
		line = ft_substr_gnl(*buff, end);
		ft_new_buff_gnl(buff, end + 1);
		return (line);
	}
	line = ft_strjoin_gnl(line, *buff);
	if (!line)
		ft_free_gnl(buff);
	*buff = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	line = NULL;
	if (fd >= 0 && fd < 10000 && BUFFER_SIZE > 0)
	{
		if (!buff)
			read_buff(fd, &buff);
		if (buff)
			line = read_line(fd, &buff);
		if (!line)
			ft_free_gnl(&buff);
	}
	return (line);
}
