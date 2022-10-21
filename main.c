/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:02:29 by snouae            #+#    #+#             */
/*   Updated: 2022/10/19 14:49:10 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;
	int		i;

	if (ac != 2 || ft_strcmp(ft_strrchr(av[1], '.'), ".cub"))
	{
		printf("map name is wrong !!");
		return (0);
	}
	ft_read(av[1], &map);
	map.top = 0;
	map.big_width = 0;
	map.check = 0;
	i = 0;
	while (map.m[i])
		i++;
	map.leng_map = i;
	i = 0;
	while (map.m[i])
		printf("%s\n", map.m[i++]);
	if (!ft_check_path(&map))
	{
		printf("The map is incorrect, reconfigure it !!!!!!!!!!!");
		return (1);
	}
		map.key_w = 0;
		map.key_s = 0;
		map.key_A = 0;
		map.key_D = 0;
		map.key_right = 0;
		map.key_left = 0;
	map.mlx_ptr = mlx_init();
	map.win_ptr = mlx_new_window(map.mlx_ptr, WIDTH, HEIGHT, "cub3d");
	map.data.img = mlx_new_image(map.mlx_ptr, WIDTH, HEIGHT);
	map.data.addr = mlx_get_data_addr(map.data.img,
			&map.data.bits_per_pixel,
			&map.data.line_length,
			&map.data.endian);
	ft_inti_angl_player(&map);
	draw_map(&map);
	mlx_loop_hook(map.mlx_ptr, deal_key, &map);
	mlx_hook(map.win_ptr, 02, (1L << 0), check_deal_key, &map);
	mlx_hook(map.win_ptr, 03, (1L << 1),  keyrealeased, &map);
	mlx_loop(map.mlx_ptr);
	return (0);
}
