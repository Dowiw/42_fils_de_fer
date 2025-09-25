/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_angles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:25:48 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 08:26:05 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"

/**
 * - Calculate rotations in the x-axis
 */
static void	rotate_x(t_map *map, double *y, double *z)
{
	double	y_x;
	double	z_x;

	y_x = *y * cos(map->rot_x) - *z * sin(map->rot_x);
	z_x = *y * sin(map->rot_x) + *z * cos(map->rot_x);
	*y = y_x;
	*z = z_x;
}

/**
 * - Calculate rotations in the y-axis
 */
static void	rotate_y(t_map *map, double *x, double *z)
{
	double	x_y;
	double	z_y;

	x_y = *x * cos(map->rot_y) + *z * sin(map->rot_y);
	z_y = -(*x) * sin(map->rot_y) + *z * cos(map->rot_y);
	*x = x_y;
	*z = z_y;
}

/**
 * - Calculate rotations in the z-axis
 */
static void	rotate_z(t_map *map, double *x, double *y)
{
	double	x_z;
	double	y_z;

	x_z = *x * cos(map->rot_z) - *y * sin(map->rot_z);
	y_z = *x * sin(map->rot_z) + *y * cos(map->rot_z);
	*x = x_z;
	*y = y_z;
}

/**
 * - Rotation calculations based on the rotation matrices
 * - NOTE: https://en.wikipedia.org/wiki/Rotation_matrix
 * - EXPLANATION: using matrix multiplication, one can combine all angles of
 * 	a 3D point for it to be moved by some angle theta.
 */
static void	calc_rotations(t_map *map, double *x, double *y, double *z)
{
	rotate_x(map, y, z);
	rotate_y(map, x, z);
	rotate_z(map, x, y);
}

/**
 * - EXPLANATION: to calculate the 2d perspective of a 3d point using isometry,
 * 	one must first calculate the rotations it takes to move the point into
 * 	isometric view. In this case, I use M_PI / 6 which is 30 degrees in both
 * 	the x-axis and y-axis (z-combined). In a real isometric view, the degrees
 *  are actually 45 in x and 35.56... in z but 30 is enough for me to use.
 *
 * @param x the abscissa
 * @param y the ordinate
 * @param z the altitude
 * @param map data of rotations, scaling and offset
 */
t_pixel	calc_iso(t_map *map, int x, int y, int z)
{
	t_pixel	p;
	double	offset[2];
	double	x_d;
	double	y_d;
	double	z_d;

	x_d = (double)x;
	y_d = (double)y;
	z_d = (double)z * map->z_scale;
	offset[0] = map->offset_w;
	offset[1] = map->offset_h;
	calc_rotations(map, &x_d, &y_d, &z_d);
	p.x = (int)(((x_d - y_d) * cos(map->view)) * map->size + offset[0]);
	p.y = (int)((-z_d + (x_d + y_d) * sin(map->view)) * map->size + offset[1]);
	if (map->orth_view)
	{
		p.x = x_d * map->size + offset[0];
		p.y = y_d * map->size + offset[1];
	}
	return (p);
}
