/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:25:10 by snouae            #+#    #+#             */
/*   Updated: 2022/10/03 17:29:14 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_read(char *path, t_map *map)
{
	char	*line;
	int		fd;
	char	*buf;

	buf = NULL;
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

