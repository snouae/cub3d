/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:02:29 by snouae            #+#    #+#             */
/*   Updated: 2022/09/25 13:37:40 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cherche_symbol(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (cherche_symbol(str[i], " \t\n"))
		i++;
	return (i);
}

int search_way(t_map *map, char *way, int *i, int *j)
{
	int k;
	
	k = 0;
	while (way[k] && map->m[*i][*j] && map->m[*i][*j] == way[k])
	{
		k++;
		(*j)++;
	}
	if(cherche_symbol(map->m[*i][*j], " \t"))
		return (1);
	return (0);
}

int check_colors(t_map *map, char *way, int *i, int *j)
{
	char	*nbr;
	int		k;
	char *tmp;
	 
	k = 0;
	nbr = NULL;
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	while (map->m[*i][*j])
	{
		if(map->m[*i][*j] != ',')
		{
			tmp[0] = map->m[*i][*j];
			nbr = ft_strjoin(nbr, tmp);
		}
		if(map->m[*i][*j] && (map->m[*i][*j] == ',' || *j == ft_strlen(map->m[*i]) - 1))
		{
			if(ft_atoi(nbr) < 0 || ft_atoi(nbr) > 255)
				return (0);
			if (!ft_strcmp("F", way))
				map->f[k++] = ft_atoi (nbr);
			else if (!ft_strcmp("C", way))
				map->c[k++] = ft_atoi (nbr);
			if(k > 3)
				return (0);
			nbr = NULL;
		}
		(*j)++;
	}
	if(k < 3 || map->m[*i][*j - 1] == ',')
		return (0);
	return (1);
}

int	ft_valid_line(t_map *map, int *i, int *j)
{
	while (map->m[*i][*j] && cherche_symbol(map->m[*i][*j], " \t\n"))
		(*j)++;
	if(map->m[*i][*j])
	{
		if(!search_way(map, "F", i, j) && !search_way(map, "NO", i, j) 
		&& !search_way(map, "WE", i, j) && !search_way(map, "EA", i, j) 
		&& !search_way(map, "C", i, j) && !search_way(map, "SO", i, j))
			return (0);
	}
	return (1);
}

int	ft_valid_path(t_map *map, char *way, int *i, int *j)
{
	char *path;
	char *tmp;

	tmp = (char *)malloc(sizeof(char) * 2);
	path = NULL;
		*j += skip_spaces(&map->m[*i][*j]);
	if(!*j && *i > map->top)
		return (0);
	if(!ft_strcmp("F", way) || !ft_strcmp("C", way))
	{
		if(!check_colors(map, way, i, j))
			return (0);
	}
	else
	{
		while (map->m[*i][*j])
		{
			tmp[0] = map->m[*i][*j];
			path = ft_strjoin(path, tmp);
			(*j)++;
		}
		// if(open(path, O_RDONLY) == -1)
		// 	 	return (0);
	}
	return (1);
}

int	caracter_exit(t_map *map, int i, int *j)
{
	if (map->m[i][*j] != '1' && map->m[i][*j] != '0' && map->m[i][*j] != 'N'
	&& map->m[i][*j] != 'S' && map->m[i][*j] != 'E' && map->m[i][*j] != 'W'
	&& map->m[i][*j] != ' ')
		return (0);
	return (1);
}
int skip_lines(t_map *map, int i)
{
	int k;
	
	k = 0;
	while (map->m[i][k] && cherche_symbol(map->m[i][k], " \t\n"))
		k++;
	if(!map->m[i][k])
		return (1);
	return (0);
}
int	check_walls(t_map *map, int i, int *j)
{
	int k;
	k = i + 1;
	while (map->m[k] && skip_lines(map, k))
		k++;
	if (!map->m[k])
		return (0);
	if(i ==  map->top || i == map->leng_map - 1 
		|| *j == 0 || *j == ft_strlen(map->m[i]) - 1)
			return (0);
	if(map->m[i][*j + 1] == ' ' || map->m[i][*j - 1] == ' '
		|| (map->m[i + 1][*j] && map->m[i + 1][*j] == ' ') || map->m[i - 1][*j] == ' ')
			return (0);
	return (1);
}
int check_wall_broken(t_map *map, int i, int *j, int leng)
{
	int k;
	
	if(leng > ft_strlen(map->m[i]))
	{
		k =  ft_strlen(map->m[i]);
		while (map->m[i - 1][k])
		{
			if(map->m[i - 1][k] != '1' && map->m[i - 1][k] != ' ')
				return (0);
			k++;
		}
	}
	else if (ft_strlen(map->m[i]) > leng)
	{
		k =  leng;
		while (map->m[i][k])
		{
			if(map->m[i][k] != '1' && map->m[i][k] != ' ')
				return (0);
			k++;
		}
	}
	return (1);
}
int flg = 0;
int ft_handle_map(t_map *map, int i, int *j)
{
		int leng;
		if(map->top && i >= map->top)
		{
			if(map->big_width < ft_strlen(map->m[i]))
				map->big_width = ft_strlen(map->m[i]);
			*j = skip_spaces(map->m[i]);
			if(map->m[i][*j] == '\0')
			{
				flg = 1;
				return (1);
			}
			*j = 0;
			if(i > map->top)
				leng = ft_strlen(map->m[i - 1]);
			while (map->m[i][*j])
			{
				if(map->m[i][*j] == '1')
					map->rows = (i - map->top) + 1;
				if(!caracter_exit(map, i, j))
					return (0);
				if (map->m[i][*j] == '0')
				{
					if(!check_walls(map,i,j))
						return (0);
					if(!check_wall_broken(map,i,j,leng))
						return (0);
				}
				if(flg == 1)
					return (0);
				(*j)++;
			}
		}
		return (1);
}
int path_exit(t_map *map, char *way)
{
	int i;
	int j;
	int c;

	i = 0;
	j = 0;
	c = 0;
	map->flags = 0;
	while (map->m[i])
	{
		j = 0;
		j =  skip_spaces(map->m[i]);
		if(map->m[i][j] == '1' && !map->flags)
		{
			map->top = i;
			map->flags = 1;
		}
		if (search_way(map, way, &i, &j))
		{
			if(!ft_valid_path(map, way, &i, &j))
				return (0);
			c++; 
		}
		else if (!map->top)
		{
			if(!ft_valid_line(map, &i, &j))
				return (0);
		}
		if(!ft_handle_map(map,i, &j))
			return (0);
		i++;
	}
	flg = 0;
	if(c != 1)
		return (0);
	return (1);
}

int ft_check_path(t_map *map)
{
	if(!path_exit(map, "NO"))
		return (0);
	if(!path_exit(map, "SO"))
		return (0);
	if(!path_exit(map, "WE"))
		return (0);
	if(!path_exit(map, "EA"))
		return (0);
	if(!path_exit(map, "F"))
		return (0);
	if(!path_exit(map, "C"))
		return (0);
	return (1);
}

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
int zoom = 30;
void draw_map(t_map *map)
{
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->rows * 20, map->big_width * 20, "cub3d");
	map->data.img = mlx_new_image(map->win_ptr, map->rows * 20, map->big_width * 20);
	map->data.addr = mlx_get_data_addr(map->data.img, &map->data.bits_per_pixel, &map->data.line_length, &map->data.endian);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
	mlx_loop(map->mlx_ptr);
}

int main(int ac, char **av)
{
    t_map map;
	if (ac != 2 || ft_strcmp(ft_strrchr(av[1], '.'), ".cub"))
	{
		printf("map name is wrong !!");
		return (0);
	}
    ft_read(av[1] ,&map);
	map.top = 0;
	map.big_width = 0;
	int i = 0;
	while(map.m[i])
		i++;
	map.leng_map = i;
	i = 0;
	while (map.m[i])
		printf("%s\n",map.m[i++]);
	if(!ft_check_path(&map))
	{
		printf("The map is incorrect, reconfigure it !!!!!!!!!!!");
		return (1);
	}
	draw_map(&map);
}