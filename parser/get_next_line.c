/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:00:06 by snouae            #+#    #+#             */
/*   Updated: 2022/09/25 14:01:59 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_get_str(int fd, char *str)
{
	char	*buf;
	int		byt;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byt = 1;
	while (!ft_strchr(str, '\n') && byt)
	{
		byt = read(fd, buf, BUFFER_SIZE);
		if (byt == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[byt] = '\0';
		str = ft_strjoin(str, buf);
	}
	free (buf);
	return (str);
}

char	*ft_select(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_select2(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free (str);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (NULL);
	i++;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free (str);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_get_str(fd, str);
	if (!str)
		return (NULL);
	line = ft_select(str);
	str = ft_select2(str);
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	fd1 = open("kkk.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}*/