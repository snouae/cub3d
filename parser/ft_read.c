/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:25:10 by snouae            #+#    #+#             */
/*   Updated: 2022/09/25 14:27:08 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_read(char *path, t_map *map)
{
	char	*line;
	int		fd;
	char	*buf;

	buf = NULL;
	int i;
	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		if(line[0] == '\n')
		{
			line[0] = ' ';
			line[1]	= '\n';
			line[2] = '\0';
		}		
		buf = ft_strjoin(buf, line);
		free(line);
		line = get_next_line(fd);
	}
	map->m = ft_split(buf, '\n');
	free(buf);
	close(fd);
}

