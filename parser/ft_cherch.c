/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cherch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:44:41 by snouae            #+#    #+#             */
/*   Updated: 2022/09/25 14:45:24 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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