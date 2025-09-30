/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:39:21 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 16:39:21 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"

/**
 * - Helper to calculate isometric size
 *
 * @param min min[0] is min_x, min[1] is min_y
 * @param max max[0] is max_x, max[1] is max_y
 */
static void	calc_iso_size(t_map *map, double min[2], double max[2])
{
	int		x;
	int		y;
	t_pixel	p;

	p.x = 0;
	p.y = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			p = calc_view(map, x, y, map->z_arr[y][x]);
			if (p.x < min[0])
				min[0] = (double)p.x;
			if (p.x > max[0])
				max[0] = (double)p.x;
			if (p.y < min[1])
				min[1] = (double)p.y;
			if (p.y > max[1])
				max[1] = (double)p.y;
			x++;
		}
		y++;
	}
}

/**
 * - Calculate the size dynamically
 * - Only for initial size
 */
double	calc_size(t_map *map)
{
	double	min[2];
	double	max[2];
	double	margin;
	double	scale_x;
	double	scale_y;

	margin = 0.6;
	min[0] = 1.79769313486231570e+308;
	min[1] = 1.79769313486231570e+308;
	max[0] = -1.79769313486231570e+308;
	max[1] = -1.79769313486231570e+308;
	calc_iso_size(map, min, max);
	scale_x = (WIN_W * margin) / (max[0] - min[0]);
	scale_y = (WIN_H * margin) / (max[1] - min[1]);
	if (scale_x < scale_y)
		return (scale_x);
	else
		return (scale_y);
}
