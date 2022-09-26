/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:02:29 by snouae            #+#    #+#             */
/*   Updated: 2022/09/26 02:27:20 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_map(t_map *map)
{
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->big_width * 32, (map->rows) * 32, "cub3d");
	map->data.img = mlx_new_image(map->mlx_ptr, map->big_width * 32, (map->rows) * 32);
	map->data.addr = mlx_get_data_addr(map->data.img, &map->data.bits_per_pixel, &map->data.line_length, &map->data.endian);
	float i = 0;
	int it = 0;
	float j;
	int h = 0;
	int t1 = 0;
	int t2 = 0;

	int i1=map->top, j1=0;
	while (i1 < map->rows + map->top)
	{
		j1 = 0;
		while (map->m[i1][j1])
		{
			if(map->m[i1][j1] == '1')
			{
				i = it * 32;
				t1 = i + 32;
				while (i < t1)
				{
					j = j1 * 32;
					t2 = j + 32;
					while (j < t2)
					{
						my_mlx_pixel_put(&map->data, j, i, 0x00FFFFFF);
						j++;
					}
					i++;
				}
			}
			else if (map->m[i1][j1] == 'N')
			{
				i = it * 32;
				t1 = i + 32;
				while (i < t1 - 32)
				{
					j = j1 * 32;
					t2 = j + 32;
					while (j < t2)
					{
						my_mlx_pixel_put(&map->data, j, i, 0x00FF0000);
						j++;
					}
					i++;
				}
			}
			j1++;
		}
		i1++;
		it++;
	}
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
	map.check = 0;
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