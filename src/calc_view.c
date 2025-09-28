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
 * - How
 */
t_pixel do_two_point(t_map *map, double *x, double *y, double *z)
{
	double focal_length = 500.0;
	double d = 10.0;
	double camera_tilt = 0.3; // radians, adjust for desired tilt
	double offset_x = map->offset_w + 100; // shift right
	double offset_y = map->offset_h - 50;  // shift up
	t_pixel p;

	// Tilt camera downward
	double z_tilted = *z * cos(camera_tilt) + *y * sin(camera_tilt);

	double denom = *y + d;
	if (denom < 1.0) denom = 1.0; // or another small positive value
	p.x = (int)(focal_length * (*x) / denom + offset_x);
	p.y = (int)(focal_length * (-z_tilted) / denom + offset_y);
	return p;
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
