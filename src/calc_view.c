/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:12:59 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/28 23:13:05 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include <math.h>
#include <stdio.h>

/**
* - EXPLANATION: to calculate the 2d perspective of a 3d point using isometry,
* 	one must first calculate the rotations it takes to move the point into
* 	isometric view. In this case, I use M_PI / 6 which is 30 degrees in both
* 	the x-axis and y-axis (z-combined). In a real isometric view, the degrees
*  are actually 45 in x and 35.56... in z but 30 is enough for me to use.
*/
t_pixel	do_iso_view(t_map *map, double *x, double *y, double *z)
{
	double	offset[2];
	t_pixel	p;

	offset[0] = map->offset_w;
	offset[1] = map->offset_h;
	p.x = (int)(((*x - *y) * cos(map->view)) * map->size + offset[0]);
	p.y = (int)((-*z + (*x + *y) * sin(map->view)) * map->size + offset[1]);
	return (p);
}

/**
 * - Do a two point perspective rendering
 *
 * EXPLANATION:
 * - f is the focal length which determines how close the points are among
 *  each other.
 * - d is the distance of the camera from the y axis
 * - big reason why z is negative is because the 2d.y is rendered from top-left
 * 	to bottom-left
 */
t_pixel	do_two_point(t_map *map, double *x, double *y, double *z)
{
	double	dnom;
	double	f;
	double	d;
	t_pixel	p;

	f = 500.0;
	d = 10.0;
	dnom = *y + d;
	if (dnom < 1.0)
		dnom = 1.0;
	p.x = (int)(f * (*x + 1.0) / dnom + map->offset_w);
	p.y = (int)(f * (-(*z * cos(0.3) + *y * sin(0.3))) / dnom + map->offset_w);
	return (p);
}

t_pixel	do_x_view(t_map *map, double *y, double *z)
{
	double	offset[2];
	t_pixel	p;

	offset[0] = map->offset_w;
	offset[1] = map->offset_h;
	p.x = (int)(-(*y) * map->size + offset[0]);
	p.y = (int)(-(*z) * map->size + offset[1]);
	return (p);
}

t_pixel	do_y_view(t_map *map, double *x, double *z)
{
	double	offset[2];
	t_pixel	p;

	offset[0] = map->offset_w;
	offset[1] = map->offset_h;
	p.x = (int)(-(*x) * map->size + offset[0]);
	p.y = (int)(-(*z) * map->size + offset[1]);
	return (p);
}

t_pixel	do_z_view(t_map *map, double *x, double *y)
{
	double	offset[2];
	t_pixel	p;

	offset[0] = map->offset_w;
	offset[1] = map->offset_h;
	p.x = (int)(*x * map->size + offset[0]);
	p.y = (int)(*y * map->size + offset[1]);
	return (p);
}
