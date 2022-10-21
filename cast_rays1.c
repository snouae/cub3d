/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:21:15 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/19 19:36:07 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int jj = 0;

static void	drawe_cub(t_map *map, int i, int j, int color)
{
	int	i1;
	int	t1;
	int	j1;
	int	t2;

	t2 = i * TILESIZE * 0.25;
	t1 = j * TILESIZE * 0.25;
	i1 = 0;
	while (i1 < TILESIZE * 0.25)
	{
		j1 = 0;
		while (j1 < TILESIZE * 0.25)
		{
			my_mlx_pixel_put(&map->data, (j1 + t1), (i1 + t2), color);
			j1++;
		}
		i1++;
	}
}

static void ft_ix(t_map *map)
{
	int	i;
	int	j;
	int	i1;

	i = map->top;
	j = 0;
	i1 = 0;
	while (i < map->rows + map->top)
	{
		j = 0;
		while (map->m[i][j])
		{
			if (map->m[i][j] == '1')
				drawe_cub(map, i1, j, 0x0000FF);
			// else if (map->m[i][j] != ' ')
			// 	drawe_cub(map, i1, j, 0x000000);
			j++;
		}
		i++;
		i1++;
	}
	my_mlx_pixel_put(&map->data, map->px*0.25, map->py*0.25, 0x00FFF);
	my_mlx_pixel_put(&map->data, map->px*0.25, map->py*0.25 - 1, 0x00FFF);
	my_mlx_pixel_put(&map->data, map->px*0.25 + 1, map->py*0.25, 0x00FFF);
	my_mlx_pixel_put(&map->data, map->px*0.25, map->py*0.25 + 1, 0x00FFF);
	my_mlx_pixel_put(&map->data, map->px*0.25 - 1, map->py*0.25, 0x00FFF);
}
void render3d(t_map *map, int num_rays)
{
    int i;

    i = 0;
    while(i < num_rays)
    {
            double  distance = map->ray[i];
            // float rayDistance = distance;
            // distance = cos(fov) * rayDistance;
            double  distanceprojectplane =  ((WIDTH / 2) / fabs(tan(M_PI / 6)));
            //printf("the height is %f\n", distanceprojectplane);
            //float h = (TILESIZE / rayDistance) * distanceprojectplane;
  			double h = ((double)TILESIZE / distance) * distanceprojectplane;
             double i1 = (((map->rows) * (double)TILESIZE / 2) - (h / 2));
             double down = h  + i1;

			
            jj += 1;
        i++;
    }
	//ft_ix(map);
}

int	cast_rays(t_map *map)
{
	double	rayangle;
	int		rays;
	float	fov;

	fov = 60 * (PI / 180);
	rayangle = map->pa - (fov / 2);
	rays = -1;
	map->ray = (float *)malloc(sizeof(float) * WIDTH);
	jj = 0;
	while (++rays < WIDTH)
	{
		if (rays == WIDTH / 2)
			castray(map, normalize_angle(rayangle), rays);
		rayangle += fov / WIDTH;
	}
	render3d(map, WIDTH);
	return (0);
}

float Distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void	castray(t_map *map, double rayangle, int i)
{
	t_pos	h_pos;
	t_pos	v_pos;
	t_pos	pos;

	h_pos = get_horizontal_intersect(map, rayangle);
	v_pos = get_vertical_intersect(map, rayangle);
	// printf("h_x: %f, h_y: %f\n", h_pos.x, h_pos.y);
	// printf("v_x: %f, v_y: %f\n", v_pos.x, v_pos.y);
	pos = get_shortest_dist(map, h_pos, v_pos);
	// printf("x: %f, y: %f\n", pos.x, pos.y);
	map->ray[i] = Distance(map->px, map->py, pos.x, pos.y) * cos(rayangle - map->pa);
	//drawline(map, map->px * 0.25, map->py * 0.25, pos.x * 0.25, pos.y * 0.25);
}

t_pos	get_shortest_dist(t_map *map, t_pos h_pos, t_pos v_pos)
{
	double	v_dist;
	double	h_dist;

	v_dist = sqrt(pow(map->px - v_pos.x, 2) + pow(map->py - v_pos.y, 2));
	h_dist = sqrt(pow(map->px - h_pos.x, 2) + pow(map->py - h_pos.y, 2));
	// printf("map->px %f | map->py %f\n", map->px, map->py);
	// printf("v_dist %f | h_dist %f\n", v_dist, h_dist);
	if (v_dist - h_dist >= 0)
		return (h_pos);
	return (v_pos);
}

void	set_ray_direction(double rayangle, t_ray *ray)
{
	if (rayangle > 0 && rayangle < PI)
		ray->is_down = 1;
	else
		ray->is_down = 0;
	if (!(ray->is_down))
		ray->is_up = 1;
	else
		ray->is_up = 0;
	if (rayangle < 0.5 * PI || rayangle > 1.5 * PI)
		ray->is_right = 1;
	else
		ray->is_right = 0;
	if (!(ray->is_right))
		ray->is_left = 1;
	else
		ray->is_left = 0;
}

t_pos	get_vertical_intersect(t_map *map, double rayangle)
{
	t_pos	pos;
	t_ray	ray;

	pos.x = WIDTH;
	pos.y = HEIGHT;
	set_ray_direction(rayangle, &ray);
	ray.xintercept = floor(map->px / TILESIZE) * TILESIZE;
	if (ray.is_right)
		ray.xintercept += TILESIZE;
	ray.yintercept = map->py + (ray.xintercept - map->px) * tan(rayangle);
	ray.xstep = TILESIZE;
	if (ray.is_left)
		ray.xstep *= -1;
	ray.ystep = TILESIZE * tanf(rayangle);
	if (ray.is_up && ray.ystep > 0)
			ray.ystep *= -1;
	else if (ray.is_down && ray.ystep < 0)
			ray.ystep *= -1;
	if (ray.is_left)
		ray.xintercept--;
	// printf("v_xintercept: %f  ", ray.xintercept);
	// printf("v_yintercept: %f\n", ray.yintercept);
	// printf("v_xstep %f  ", ray.xstep);
	// printf("v_ystep %f\n", ray.ystep);
	while (69 && !0)
	{
		pos.x = ray.xintercept;
		pos.y = ray.yintercept;
		if (ray.yintercept > (map->rows) * TILESIZE || ray.yintercept <= 0
			|| ray.xintercept > map->big_width * TILESIZE || ray.xintercept <= 0)
			return (pos);
		if (map->m[(int)ray.yintercept / TILESIZE + map->top]
			[(int)ray.xintercept / TILESIZE] != '0')
			return (pos);
		ray.xintercept += ray.xstep;
		ray.yintercept += ray.ystep;
	}
	return (pos);
}

t_pos	get_horizontal_intersect(t_map *map, double rayangle)
{
	t_pos	pos;
	t_ray	ray;

	pos.x = WIDTH;
	pos.y = HEIGHT;
	set_ray_direction(rayangle, &ray);
	ray.yintercept = floor(map->py / TILESIZE) * TILESIZE;
	if (ray.is_down)
		ray.yintercept += TILESIZE;
	ray.xintercept = map->px + (ray.yintercept - map->py) / tanf(rayangle);
	ray.ystep = TILESIZE;
	if (ray.is_up)
		ray.ystep *= -1;
	ray.xstep = TILESIZE / tan(rayangle);
	if (ray.is_left && ray.xstep > 0)
			ray.xstep *= -1;
	else if (ray.is_right && ray.xstep < 0)
			ray.xstep *= -1;
	if (ray.is_up)
		ray.yintercept--;
	// printf("h_xintercept: %f  ", ray.xintercept);
	// printf("h_yintercept: %f\n", ray.yintercept);
	// printf("h_xstep %f  ", ray.xstep);
	// printf("h_ystep %f\n", ray.ystep);
	while (69)
	{
		pos.x = ray.xintercept;
		pos.y = ray.yintercept;
		if (ray.yintercept > (map->rows) * TILESIZE || ray.yintercept < 0
			|| ray.xintercept > map->big_width * TILESIZE || ray.xintercept < 0)
			return (pos);
		if (map->m[(int)ray.yintercept / TILESIZE + map->top]
			[(int)ray.xintercept / TILESIZE] != '0')
			return (pos);
		ray.xintercept += ray.xstep;
		ray.yintercept += ray.ystep;
	}
	return (pos);
}

void	drawline(t_map *map, double x0, double y0, double x1, double y1)
{
	t_dda	dda;
	int		i;

	dda.dx = x1 - x0;
	dda.dy = y1 - y0;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.step = fabs(dda.dx);
	else
		dda.step = fabs(dda.dy);
	dda.xinc = dda.dx / dda.step;
	dda.yinc = dda.dy / dda.step;
	i = 0;
	while (++i <= dda.step)
	{
		my_mlx_pixel_put(&map->data, x0, y0, 0xFF0000);
		x0 += dda.xinc;
		y0 += dda.yinc;
	}
}

double	normalize_angle(double angle)
{
	if (angle > 2 * PI)
		return (angle - (2 * PI));
	else if (angle <= 0)
		return (angle + (2 * PI));
	if (angle == M_PI || angle == 0)
		angle += 0.000001;
	return (angle);
}
