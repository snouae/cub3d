/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:57:26 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/20 18:35:46 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>
double	pdx;
double	pdy;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x < WIDTH && y < HEIGHT && x > 0 && y > 0)
	{	
		pixel = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) pixel = color;
	}
}

void	draw_cub(t_map *map, int i, int j, int color)
{
	int	i1;
	int	t1;
	int	j1;
	int	t2;

	t2 = i * TILESIZE;
	t1 = j * TILESIZE;
	i1 = 0;
	while (i1 < TILESIZE)
	{
		j1 = 0;
		while (j1 < TILESIZE)
		{
			my_mlx_pixel_put(&map->data, (j1 + t1), (i1 + t2), color);
			j1++;
		}
		i1++;
	}
}

int	destroy_notif(void)
{
	printf("GAME CLOSED\n");
	exit (0);
}

void	ft_pixel(t_map *map)
{
	// int i;
	// int j;
	// int i1;

	// i = 0, j = 0, i1 = 0;
	// while (i < HEIGHT)
	// {
	// 	j = 0;
	// 	while (j < WIDTH)
	// 	{
	// 		// if(map->m[i][j] == '1')
	// 			draw_cub(map, i1 ,j, 0x236F21);
	// 		// else if (map->m[i][j] != ' ')
	// 		// 	draw_cub(map, i1 ,j, 0x00FFFF, 0);
	// 		j++;
	// 	}
	// 	i++;
	// 	i1++;
	// }

	// i = 0, j = 0, i1 = 0;
	// while (i < HEIGHT / 20)
	// {
	// 	j = 0;
	// 	while (j < WIDTH / 20)
	// 	{ 
	// 		draw_cub(map, i1 ,j, 0x87CEEB);
	// 		j++;
	// 	}
	// 	i++;
	// 	i1++;
	// }
	cast_rays(map);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data.img, 0, 0);
}

int check_deal_key(int key, t_map *map)
{
	//printf("the key is %d\n", key);
	if (key == 53)
		destroy_notif();
	if(key == W)
		map->key_w = 1;
	else if(key == S)
		map->key_s = 1;
	else if(key == A)
		map->key_A = 1;
	else if(key == D)
		map->key_D = 1;
	else if(key == 124)
		map->key_right = 1;
	else if (key == 123)
		map->key_left = 1;
	//deal_key(map);
	return (0);
}

int keyrealeased(int key, t_map *map)
{
	if(key == W)
		map->key_w = 0;
	else if(key == S)
		map->key_s = 0;
	else if(key == A)
		map->key_A = 0;
	else if(key == D)
		map->key_D = 0;
	else if(key == 124)
		map->key_right = 0;
	else if (key == 123)
		map->key_left = 0;
	return (0);
}
int	deal_key(t_map *map)
{
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	if(map->key_left == 1)
	{
		map->pa -= 0.1;
		if (map->pa < 0)
			map->pa += 2 * PI;
	}
	if(map->key_right == 1)
	{
		map->pa += 0.1;
		if (map->pa > 2 * PI)
			map->pa -= 2 * PI;
	}
	pdx = cos(map->pa) * 1;
	pdy = sin(map->pa) * 1;
	if (map->key_s == 1)
	{
		map->py -= pdy;
		map->px -= pdx;
		if(map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE] != '0')
		{
			map->py += pdy;
			map->px += pdx;
		}
	}
	if (map->key_w == 1)
	{
		map->py += pdy;
		map->px += pdx;
		if(map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE] != '0')
		{
			map->py -= pdy;
			map->px -= pdx;
		}
	}
	if (map->key_A == 1)
	{
		pdx = cos(fabs(map->pa - M_PI_2)) * 1;
		pdy = sin(fabs(map->pa - M_PI_2)) * 1;;
		map->py += pdy;
		map->px += pdx;
		if(map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE] != '0')
		{
			map->py -= pdy;
			map->px -= pdx;
		}
	}
	if (map->key_D == 1)
	{
		pdx = cos(fabs(map->pa + M_PI_2)) * 1;
		pdy = sin(fabs(map->pa + M_PI_2)) * 1;;
		map->py += pdy;
		map->px += pdx;
		if(map->m[(int)map->py / TILESIZE + map->top][(int)map->px / TILESIZE] != '0')
		{
			map->py -= pdy;
			map->px -= pdx;
		}
	}
	draw_map(map);
	return (0);
}
void ft_inti_angl_player(t_map *map)
{
	if (map->view == 'N')
		map->pa = (3 * PI) / 2;
	else if (map->view == 'S')
		map->pa = (PI) / 2;
	else if (map->view == 'W')
		map->pa = PI;
	else if (map->view == 'E')
		map->pa = 0;
	pdx = cos(map->pa) * 5;
	pdy = sin(map->pa) * 5;
}

void	draw_map(t_map *map)
{
	ft_pixel(map);
}
