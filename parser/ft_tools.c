/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:28:41 by snouae            #+#    #+#             */
/*   Updated: 2022/10/03 17:26:54 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (!s)
		return (NULL);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

char *ft_strdup(char *s)
{
	char *new;
	int leng;
	int i;

	leng = ft_strlen(s);
	i = 0;
	new = (char *)malloc(sizeof(char) * (leng + 1));
	while (s[i])
	{
		new[i] =  s[i];
		i++;
	}
	return (new);
}

int	ft_checknumber(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	s;

	s = 0;
	i = 0;
	if(!str)
		return (-1);
	while (str[i] <= 32)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			s = s * 10 + str[i] - '0';
		else if((str[i] <= 32))
		{
			while (str[i] && (str[i] <= 32))
				i++;
			if(str[i] == '\0')
				return (s);
			return (-1);
		}
		else if(!(str[i] <= 32))
			return (-1);
		i++;
	}
	return (s);
}

